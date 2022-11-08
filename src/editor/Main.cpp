#include "MainWindow.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Invalid amount of parameters." << std::endl;
        return -1;
    }

    QApplication a(argc, argv);
    MainWindow w(0, argv[1]);
    w.show();
    return a.exec();
}
