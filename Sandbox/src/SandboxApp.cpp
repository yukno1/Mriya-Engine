#include <Miriya.h>

class Sandbox : public Miriya::Application {
   public:
   Sandbox() {}
   ~Sandbox() {}
};


Miriya::Application* Miriya::CreateApplication() {
   return new Sandbox();
}