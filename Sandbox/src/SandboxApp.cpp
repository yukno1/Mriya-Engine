#include <Miriya.h>
class ExampleLayer : public Miriya::Layer {
public:
   ExampleLayer(): Layer("Example") {
   }

   void OnUpdate() override {
      MIR_INFO("ExampleLayer::Update");
   }

   void OnEvent(Miriya::Event& event) override {
      MIR_TRACE("{0}", event.ToString());
   }
};


class Sandbox : public Miriya::Application {
   public:
   Sandbox() {
      PushLayer(new ExampleLayer());
      PushOverlay(new Miriya::ImGuiLayer());
   }
   ~Sandbox() {}
};


Miriya::Application* Miriya::CreateApplication() {
   return new Sandbox();
}