#include <Miriya.h>

class ExampleLayer : public Miriya::Layer {
public:
   ExampleLayer(): Layer("Example") {
   }

   void OnUpdate() override {
      // MIR_INFO("ExampleLayer::Update");

      // if (Miriya::Input::IsKeyPressed(MIR_KEY_TAB))
      //    MIR_INFO();
   }

   void OnEvent(Miriya::Event& event) override {
      // MIR_TRACE("{0}", event.ToString());
      if (event.GetEventType() == Miriya::EventType::KeyPressed) {
         auto e = static_cast<Miriya::KeyPressedEvent &>(event);
         if (e.GetKeyCode() == MIR_KEY_TAB)
            MIR_TRACE("Tab key is pressed");
         MIR_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
      }
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