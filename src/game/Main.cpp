/**
 * Main.cpp
 *
 * @date 03.03.16
 * @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
 */
#include "MainWindow.hpp"
#include "Filesystem.hpp"

using namespace ikaruga;
using std::string;
using std::cout;
using std::endl;

/**
 * @brief Takes command line paramter and starts MainMenu
 *
 * @param argv command line parameters. You have to provide a game specific resource directory.
 * @return exit code
 */
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Invalid amount of parameters." << std::endl;
        return -1;
    }

    MainWindow window("Ikaruga", 625, 576, boost::filesystem::path(argv[1]));

    MainMenu menu(&window, boost::filesystem::path(argv[1]));
    window.setMenu(&menu);

    window.setActualScreen(MainWindow::RENDER_MAINMENU);
    window.run();

    // Free textures
    TextureFactory::instance(window.getRenderer()).deleteAll();
}
