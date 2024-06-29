#include "NTC/NTCTestComponent.h"
#include "Utils/IncubatorTestSimulatorUtils.h"


using namespace ITS;

static constexpr const char * NTC_IMAGE_PATH = "resources/images/NTC.png";
static constexpr const char *NTC_FONT_PATH = "resources/fonts/Fira_Code/static/FiraCode-Regular.ttf";
static constexpr const int32_t NTC_FONT_SIZE = 32;
static constexpr const double BASE_TEMPERATURE_IN_CELCIUS = 32;

NTCTestComponent::NTCTestComponent() :
    m_Renderer { nullptr },
    m_ImageTexture { nullptr },
    m_TextTexture { nullptr },
    m_NTCFont { nullptr },
    m_TemperatureInDegree { 50 },
    m_TemperatureStringValue { 0 }
{
}

NTCTestComponent::~NTCTestComponent()
{
    if (m_ImageTexture != nullptr)
    {
        SDL_DestroyTexture(m_ImageTexture);
    }
    if (m_TextTexture != nullptr)
    {
        SDL_DestroyTexture(m_TextTexture);
    }
}

bool NTCTestComponent::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos)
{
    bool bResult = true;
    m_Renderer = renderer;

    m_ImageRect.x = xPos;
    m_ImageRect.y = yPos;
    m_ImageRect.w = 128;
    m_ImageRect.h = 128;

    m_TextRect.x = m_ImageRect.x + 50;
    m_TextRect.y = m_ImageRect.y + 100;
    m_TextRect.w = 70;
    m_TextRect.h = 30;

    m_Slider.Initialize(m_Renderer, m_ImageRect.x, m_ImageRect.y + 130, 120, 7, 20);

    m_NTCFont = TTF_OpenFont(NTC_FONT_PATH, NTC_FONT_SIZE);
    if (m_NTCFont == nullptr)
    {
        bResult = false;
    }

    if (bResult)
    {
        SDL_Surface *ntcSurface = IMG_Load(NTC_IMAGE_PATH);
        if (ntcSurface == nullptr)
        {
            bResult = false;
        }
        else
        {
            m_ImageTexture = SDL_CreateTextureFromSurface(m_Renderer, ntcSurface);
            SDL_FreeSurface(ntcSurface);
        }
    }

    return bResult;
}


void NTCTestComponent::HandleEvents(const SDL_Event &event)
{
    m_Slider.HandleEvents(event);
}

void NTCTestComponent::Run()
{
    SDL_RenderCopy(m_Renderer, m_ImageTexture, NULL, &m_ImageRect);
    m_Slider.Run();
    m_TemperatureInDegree = BASE_TEMPERATURE_IN_CELCIUS + (double)(m_Slider.GetSliderValue()) / 10;
    memset(m_TemperatureStringValue, 0, sizeof(m_TemperatureInDegree));
    sprintf(m_TemperatureStringValue, "%.01lf ", m_TemperatureInDegree);
    size_t temperatureStringSize = strlen(m_TemperatureStringValue);
    Uint16 temperatureString[TEMPERATURE_STRING_SIZE] = { 0 };
    uint8_t index;
    for (index = 0; index < temperatureStringSize; index++)
    {
        temperatureString[index] = (Uint16) (m_TemperatureStringValue[index]);
    }
    temperatureString[index] = 0x00B0;
    index++;
    temperatureString[index] = 'C';
    
    SDL_Surface *surfaceText = TTF_RenderUNICODE_Solid(m_NTCFont ,temperatureString, {30, 213, 30});
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(m_Renderer, surfaceText);
    SDL_FreeSurface(surfaceText);
    SDL_RenderCopy(m_Renderer, textureText, NULL, &m_TextRect);
    SDL_DestroyTexture(textureText);
}
