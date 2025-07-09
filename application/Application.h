#include <iostream>
#define app Application::getInstance()

namespace shyspace
{
    class Application
    {
    public:
        ~Application();
        static Application *getInstance();
        void text()
        {
            std::cout << "text" << std::endl;
        }

    private:
        static Application *mInstance;
        Application();
    };
} // namespace shyspace