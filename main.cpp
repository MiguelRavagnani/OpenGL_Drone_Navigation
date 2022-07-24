#include "application.h"

int main(int argc, char *argv[])
{
    Application *app = new Application(800U, 600U);

    app->Run();
}