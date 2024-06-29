#include "Output/OutputSensorTestComponent.h"
#include "Utils/IncubatorTestSimulatorUtils.h"


using namespace ITS;

OutputSensorTestComponent::OutputSensorTestComponent() :
    m_Renderer { nullptr },
    m_ImageTexture { nullptr },
    m_bIsOn { false }
{
}

OutputSensorTestComponent::~OutputSensorTestComponent()
{
    if (m_ImageTexture != nullptr)
    {
        SDL_DestroyTexture(m_ImageTexture);
    }
}

bool OutputSensorTestComponent::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos, int32_t width, int32_t height, const char *imagePath)
{
    bool bResult = true;
    m_Renderer = renderer;

    m_ImageRect.x = xPos;
    m_ImageRect.y = yPos;
    m_ImageRect.w = width;
    m_ImageRect.h = height;

    m_StatusRect.x = m_ImageRect.x + m_ImageRect.w - 4;
    m_StatusRect.y = m_ImageRect.y + 4;
    m_StatusRect.w = 10;
    m_StatusRect.h = 10;

    SDL_Surface *outputComponentImageSurface = IMG_Load(imagePath);
    if (outputComponentImageSurface == nullptr)
    {
        bResult = false;
    }
    else
    {
        m_ImageTexture = SDL_CreateTextureFromSurface(m_Renderer, outputComponentImageSurface);
        SDL_FreeSurface(outputComponentImageSurface);
    }

    return bResult;
}

void OutputSensorTestComponent::Run()
{
    SDL_RenderCopy(m_Renderer, m_ImageTexture, NULL, &m_ImageRect);
    if (m_bIsOn)
    {
        SDL_SetRenderDrawColor(m_Renderer, 0, 200, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(m_Renderer, 140, 0, 0, 255);
    }
    SDL_RenderFillRect(m_Renderer, &m_StatusRect);
}
