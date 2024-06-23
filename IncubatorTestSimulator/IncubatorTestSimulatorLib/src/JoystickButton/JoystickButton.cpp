#include "JoystickButton/JoystickButton.h"

using namespace ITS;

static constexpr const char * JOYSTICK_IDLE_IMAGE_PATH = "resources/images/Joystick_Idle.png";
static constexpr const char * JOYSTICK_UP_IMAGE_PATH = "resources/images/Joystick_Up.png";
static constexpr const char * JOYSTICK_DOWN_IMAGE_PATH = "resources/images/Joystick_Down.png";
static constexpr const char * JOYSTICK_RIGHT_IMAGE_PATH = "resources/images/Joystick_Right.png";
static constexpr const char * JOYSTICK_LEFT_IMAGE_PATH = "resources/images/Joystick_Left.png";

JoystickButton::JoystickButton() :
    m_Renderer { nullptr },
    m_IdleTexture { nullptr },
    m_UpTexture { nullptr },
    m_DownTexture { nullptr },
    m_RightTexture { nullptr },
    m_LeftTexture { nullptr },
    m_UpKeyPressed { false },
    m_DownKeyPressed { false },
    m_RightKeyPressed { false },
    m_LeftKeyPressed { false },
    m_JoystickPressState { Sensors::JOYSTICK_PRESS_STATE_NOT_PRESSED }
{


}

JoystickButton::~JoystickButton()
{
    if (m_IdleTexture != nullptr)
    {
        SDL_DestroyTexture(m_IdleTexture);
    }
    if (m_UpTexture != nullptr)
    {
        SDL_DestroyTexture(m_UpTexture);
    }
    if (m_DownTexture != nullptr)
    {
        SDL_DestroyTexture(m_DownTexture);
    }
    if (m_RightTexture != nullptr)
    {
        SDL_DestroyTexture(m_RightTexture);
    }
    if (m_LeftTexture != nullptr)
    {
        SDL_DestroyTexture(m_LeftTexture);
    }
}

void JoystickButton::GetJoystickData(bool &upKeyPressed, bool &downKeyPressed, bool &rightKeyPressed, bool &leftKeyPressed)
{
    upKeyPressed = m_UpKeyPressed;
    downKeyPressed = m_DownKeyPressed;
    rightKeyPressed = m_RightKeyPressed;
    leftKeyPressed = m_LeftKeyPressed;
}

uint8_t JoystickButton::GetJoystickButtonState()
{
    uint8_t result = (uint8_t)m_JoystickPressState;
    if (m_JoystickPressState == Sensors::JOYSTICK_PRESS_STATE_CLICKED)
    {
        m_JoystickPressState = Sensors::JOYSTICK_PRESS_STATE_NOT_PRESSED;
    }
    return result;
}

bool JoystickButton::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos)
{
    bool bResult = true;
    m_Renderer = renderer;

    m_JoystickRect.x = xPos;
    m_JoystickRect.y = yPos;
    m_JoystickRect.w = 240;
    m_JoystickRect.h = 240;

    m_JoystickPressedRect.x = m_JoystickRect.x + 10;
    m_JoystickPressedRect.y = m_JoystickRect.y + 10;
    m_JoystickPressedRect.w = m_JoystickRect.w - 20;
    m_JoystickPressedRect.h = m_JoystickRect.h - 20;

    {
        SDL_Surface *idleSurface = IMG_Load(JOYSTICK_IDLE_IMAGE_PATH);
        if (idleSurface == nullptr)
        {
            bResult = false;
        }
        m_IdleTexture = SDL_CreateTextureFromSurface(m_Renderer, idleSurface);
        SDL_FreeSurface(idleSurface);
    }

    if (bResult)
    {
        SDL_Surface *upSurface = IMG_Load(JOYSTICK_UP_IMAGE_PATH);
        if (upSurface == nullptr)
        {
            bResult = false;
        }
        m_UpTexture = SDL_CreateTextureFromSurface(m_Renderer, upSurface);
        SDL_FreeSurface(upSurface);
    }

    if (bResult)
    {
        SDL_Surface *downSurface = IMG_Load(JOYSTICK_DOWN_IMAGE_PATH);
        if (downSurface == nullptr)
        {
            bResult = false;
        }
        m_DownTexture = SDL_CreateTextureFromSurface(m_Renderer, downSurface);
        SDL_FreeSurface(downSurface);
    }

    if (bResult)
    {
        SDL_Surface *rightSurface = IMG_Load(JOYSTICK_RIGHT_IMAGE_PATH);
        if (rightSurface == nullptr)
        {
            bResult = false;
        }
        m_RightTexture = SDL_CreateTextureFromSurface(m_Renderer, rightSurface);
        SDL_FreeSurface(rightSurface);
    }

    if (bResult)
    {
        SDL_Surface *leftSurface = IMG_Load(JOYSTICK_RIGHT_IMAGE_PATH);
        leftSurface = IMG_Load(JOYSTICK_LEFT_IMAGE_PATH);
        if (leftSurface == nullptr)
        {
            bResult = false;
        }
        m_LeftTexture = SDL_CreateTextureFromSurface(m_Renderer, leftSurface);
        SDL_FreeSurface(leftSurface);
    }
    return bResult;
}

void JoystickButton::HandleEvents(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                m_UpKeyPressed = true;
                break;
            case SDLK_DOWN:
                m_DownKeyPressed = true;
                break;
            case SDLK_RIGHT:
                m_RightKeyPressed = true;
                break;
            case SDLK_LEFT:
                m_LeftKeyPressed = true;
                break;
            case SDLK_o:
                m_JoystickPressState = Sensors::JOYSTICK_PRESS_STATE_PRESSED;
            default:
                break;
            }
        }
        break;

    case SDL_KEYUP:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                m_UpKeyPressed = false;
                break;
            case SDLK_DOWN:
                m_DownKeyPressed = false;
                break;
            case SDLK_RIGHT:
                m_RightKeyPressed = false;
                break;
            case SDLK_LEFT:
                m_LeftKeyPressed = false;
                break;
            case SDLK_o:
                m_JoystickPressState = Sensors::JOYSTICK_PRESS_STATE_CLICKED;
            default:
                break;
            }
        }
        break;
    }
}


void JoystickButton::Run(SDL_Event &event)
{
    SDL_Rect *joystickImageRect = &m_JoystickRect;
    HandleEvents(event);
    if (m_JoystickPressState == Sensors::JOYSTICK_PRESS_STATE_PRESSED)
    {
        joystickImageRect = &m_JoystickPressedRect;
    }

    if (m_UpKeyPressed)
    {
        SDL_RenderCopy(m_Renderer, m_UpTexture, NULL, joystickImageRect);
    }
    else if (m_DownKeyPressed)
    {
        SDL_RenderCopy(m_Renderer, m_DownTexture, NULL, joystickImageRect);
    }
    else if (m_RightKeyPressed)
    {
        SDL_RenderCopy(m_Renderer, m_RightTexture, NULL, joystickImageRect);
    }
    else if (m_LeftKeyPressed)
    {
        SDL_RenderCopy(m_Renderer, m_LeftTexture, NULL, joystickImageRect);
    }
    else
    {
        SDL_RenderCopy(m_Renderer, m_IdleTexture, NULL, joystickImageRect);
    }
}
