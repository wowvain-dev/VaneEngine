#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Core/Asserts.hpp"
#include "GameTypes.hpp"

extern Vane::Application *Vane::CreateApplication(int argc, char **argv);
bool g_ApplicationRunning = true;

namespace Vane
{
    int Main(int argc, char **argv)
    {
        // Initializing systems;
        Application *app = CreateApplication(argc, argv);

        VASSERT_MSG(app, "Client application is null!");

        app->run();

        app->shutdown();

        delete app;
        // Shutting systems down;
        VERROR("SHAT SYSTEMS DOWN");
        return 0;
    }
}

int main(int argc, char **argv)
{
    return Vane::Main(argc, argv);
}