#include "IncubatorTestSimulator.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace ITS;

IncubatorTestSimulator::IncubatorTestSimulator() : 
    m_Window { nullptr },
    m_Renderer { nullptr },
    m_SimulatorStartTimestampInMillisecond { -1 },
    m_UpKeyPressed { false },
    m_DownKeyPressed { false },
    m_RightKeyPressed { false },
    m_LeftKeyPressed { false },
    m_OKeyState { 0 }
{
}

IncubatorTestSimulator::~IncubatorTestSimulator()
{
    if (m_Window != nullptr)
    {
        SDL_DestroyWindow(m_Window);
    }
    if (m_Renderer != nullptr)
    {
        SDL_DestroyRenderer(m_Renderer);
    }
    IMG_Quit();
    SDL_Quit();
}

void IncubatorTestSimulator::SendDataToTC1602(uint8_t data)
{
    m_TC1602Screen.SendData(data);
}

void IncubatorTestSimulator::SendCommandToTC1602(uint8_t command)
{
    m_TC1602Screen.SendCommand(command);
}

bool IncubatorTestSimulator::GetHumidityPercentageAndTemperatureInCelcius(uint8_t &humidityPercentage, uint8_t &temperatureInCelcius)
{
    // TODO: Will be implemented
    humidityPercentage = 60;
    temperatureInCelcius = 34;
    return true;
}

bool IncubatorTestSimulator::GetTemperatureInCelcius(double &temperatureInCelcius)
{
    // TODO: Will be implemented
    temperatureInCelcius = 34.5;
    return true;
}

void IncubatorTestSimulator::GetJoystickData(bool &upKeyPressed, bool &downKeyPressed, bool &rightKeyPressed, bool &leftKeyPressed)
{
    m_JoystickButton.GetJoystickData(upKeyPressed, downKeyPressed, rightKeyPressed, leftKeyPressed);
}

uint8_t IncubatorTestSimulator::GetJoystickButtonState()
{
    return m_JoystickButton.GetJoystickButtonState();
}

void IncubatorTestSimulator::Initialize()
{
    InitializeTime();
    InitializeEeprom24C32();
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not be initialized" << std::endl;
        exit(127);
    }

    m_Window = SDL_CreateWindow("Inbuator Test Simulator",
        100,
        100,
        1024,
        480,
        SDL_WINDOW_SHOWN);

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (TTF_Init() == -1)
    {
        std::cerr << "Unable to Init ttf" << std::endl;
        exit(127);
    }
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((initStatus & flags) != flags)
    {
        std::cerr << "Unable to Initialize IMG" << std::endl;
        exit(127);
    }
    if (!m_TC1602Screen.Initialize(m_Renderer, 0, 0))
    {
        std::cerr << "Unable to initialize TC1602 Sreen" << std::endl;
        exit(127);
    }
    if (!m_JoystickButton.Initialize(m_Renderer, 700, 0))
    {
        std::cerr << "Unable to initialize JoystickButton" << std::endl;
        exit(127);
    }
}

void IncubatorTestSimulator::HandleEvents(SDL_Event &event)
{
    m_JoystickButton.HandleEvents(event);
}

void IncubatorTestSimulator::Run()
{
    SDL_SetRenderDrawColor(m_Renderer, 0x20, 0x20, 0x20, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);
    m_TC1602Screen.Run();
    m_JoystickButton.Run();
    SDL_RenderPresent(m_Renderer);
}

void IncubatorTestSimulator::InitializeTime()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    m_SimulatorStartTimestampInMillisecond = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void IncubatorTestSimulator::InitializeEeprom24C32()
{
    std::ifstream eeprom24C32File ("Eeprom24C32.bin", std::ios::out | std::ios::binary);
    if (!eeprom24C32File.is_open())
    {
        CreateEeprom24C32();
    }
    eeprom24C32File.open("Eeprom24C32.bin", std::ios::out | std::ios::binary);
    if (!eeprom24C32File.is_open())
    {
        std::cerr << "Unable to open Eeprom24C32.bin file!" << std::endl;
        exit(127);
    }

    eeprom24C32File.close();
}

void IncubatorTestSimulator::CreateEeprom24C32()
{
    std::ofstream eeprom24C32File ("Eeprom24C32.bin", std::ios::out | std::ios::binary);
    if (!eeprom24C32File.is_open())
    {
        std::cerr << "Unable to crate Eeprom24C32.bin file!" << std::endl;
        exit(127);
    }
    constexpr const int32_t EEPROM24C32_SIZE = 32 * 8; // Just 8 pages
    uint8_t emptyBuffer[EEPROM24C32_SIZE];
    memset(emptyBuffer, 0xFF, EEPROM24C32_SIZE);
    eeprom24C32File.write((const char*) emptyBuffer, EEPROM24C32_SIZE);
    eeprom24C32File.close();
}
