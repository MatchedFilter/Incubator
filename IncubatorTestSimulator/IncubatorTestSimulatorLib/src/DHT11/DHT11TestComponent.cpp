#include "DHT11/DHT11TestComponent.h"
#include "Utils/IncubatorTestSimulatorUtils.h"


using namespace ITS;

static constexpr const char * DHT11_IMAGE_PATH = "resources/images/DHT11.png";
static constexpr const char *DHT11_FONT_PATH = "resources/fonts/Fira_Code/static/FiraCode-Regular.ttf";
static constexpr const int32_t DHT11_FONT_SIZE = 32;

DHT11TestComponent::DHT11TestComponent() :
    m_Renderer { nullptr },
    m_ImageTexture { nullptr },
    m_TextTexture { nullptr },
    m_DHT11Font { nullptr },
    m_HumidityPercentage { 50 },
    m_HumidityStringValue { 0 },
    m_bHovered { false },
    m_bPressed { false }
{
}

DHT11TestComponent::~DHT11TestComponent()
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

bool DHT11TestComponent::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos)
{
    bool bResult = true;
    m_Renderer = renderer;

    m_ImageRect.x = xPos;
    m_ImageRect.y = yPos;
    m_ImageRect.w = 128;
    m_ImageRect.h = 128;

    m_TextRect.x = m_ImageRect.x;
    m_TextRect.y = m_ImageRect.y + 100;
    m_TextRect.w = 60;
    m_TextRect.h = 30;

    m_Slider.Initialize(m_Renderer, m_ImageRect.x, m_ImageRect.y + 130, 120, 7, 20);

    m_DHT11Font = TTF_OpenFont(DHT11_FONT_PATH, DHT11_FONT_SIZE);
    if (m_DHT11Font == nullptr)
    {
        bResult = false;
    }

    if (bResult)
    {
        SDL_Surface *dht11Surface = IMG_Load(DHT11_IMAGE_PATH);
        if (dht11Surface == nullptr)
        {
            bResult = false;
        }
        else
        {
            m_ImageTexture = SDL_CreateTextureFromSurface(m_Renderer, dht11Surface);
            SDL_FreeSurface(dht11Surface);
        }
    }

    return bResult;
}

void DHT11TestComponent::GetHumidityPercentageAndTemperature(uint8_t &humidityPercentage, uint8_t &temperature)
{
    humidityPercentage = m_HumidityPercentage;
    temperature = 34; // TODO: Will be updated from gui
}


void DHT11TestComponent::HandleEvents(const SDL_Event &event)
{
    m_Slider.HandleEvents(event);
}

void DHT11TestComponent::Run()
{
    SDL_RenderCopy(m_Renderer, m_ImageTexture, NULL, &m_ImageRect);
    m_Slider.Run();
    m_HumidityPercentage = m_Slider.GetSliderValue();
    sprintf(m_HumidityStringValue, "%%%2d", m_HumidityPercentage);
    SDL_Surface *surfaceText = TTF_RenderText_Solid(m_DHT11Font ,m_HumidityStringValue, {30, 213, 30});
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(m_Renderer, surfaceText);
    SDL_FreeSurface(surfaceText);
    SDL_RenderCopy(m_Renderer, textureText, NULL, &m_TextRect);
    SDL_DestroyTexture(textureText);
}
