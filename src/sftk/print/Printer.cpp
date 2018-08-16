#include <sftk/print/Printer.hpp>

namespace sftk {

std::ostream& operator<<(std::ostream& os, sf::Time const& t) { 
    return os << t.asSeconds() << "s";
}

std::ostream& operator<<(std::ostream& os, sf::Color const& c) {
    return os << "Color {" << c.r << ", " << c.g << ", " << c.b << "}";
}

std::ostream& operator<<(std::ostream& os, sf::ContextSettings const& c) { 
    return os << "Settings {v=" << c.majorVersion << "." << c.minorVersion << ", attrs=" << c.attributeFlags << ", rgb=" << std::boolalpha << c.sRgbCapable
              << ", " << c.depthBits << "/" << c.stencilBits << "/" << c.antialiasingLevel << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Event const& e) { 
    switch (e.type) {
        case sf::Event::Closed: 
            return os << "Event Close";
        case sf::Event::Resized: 
            return os << "Event " << e.size;
        case sf::Event::LostFocus: 
            return os << "Event Lose Focus";
        case sf::Event::GainedFocus: 
            return os << "Event Gain Focus";
        case sf::Event::TextEntered: 
            return os << "Event " << e.text;
        case sf::Event::KeyPressed: 
            return os << "Event Press " << e.key;
        case sf::Event::KeyReleased: 
            return os << "Event Release " << e.key;
        case sf::Event::MouseWheelScrolled: 
            return os << "Event " << e.mouseWheelScroll;
        case sf::Event::MouseButtonPressed: 
            return os << "Event Press " << e.mouseButton;
        case sf::Event::MouseButtonReleased: 
            return os << "Event Release " << e.mouseButton;
        case sf::Event::MouseMoved: 
            return os << "Event " << e.mouseMove;
        case sf::Event::MouseEntered: 
            return os << "Event Enter Mouse";
        case sf::Event::MouseLeft: 
            return os << "Event Leave Mouse";
        case sf::Event::JoystickButtonPressed: 
            return os << "Event Press " << e.joystickButton;
        case sf::Event::JoystickButtonReleased: 
            return os << "Event Release " << e.joystickButton;
        case sf::Event::JoystickMoved: 
            return os << "Event Move Joystick " << e.joystickMove;
        case sf::Event::JoystickConnected: 
            return os << "Event Connect Joystick {id=" << e.joystickConnect.joystickId << "}";
        case sf::Event::JoystickDisconnected: 
            return os << "Event Disconnect Joystick {id=" << e.joystickConnect.joystickId << "}";
        case sf::Event::TouchBegan: 
            return os << "Event Begin " << e.touch;
        case sf::Event::TouchMoved: 
            return os << "Event Move " << e.touch;
        case sf::Event::TouchEnded: 
            return os << "Event End " << e.touch;
        case sf::Event::SensorChanged: 
            return os << "Event " << e.sensor;

        default:
            return os << "Event Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, sf::Event::JoystickButtonEvent const& e) { 
    return os << "Joystick Button {id=" << e.joystickId << ", but=" << e.button << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Event::JoystickConnectEvent const& e) { 
    return os << "(Dis)connect Joystick {id=" << e.joystickId << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Event::JoystickMoveEvent const& e) { 
    return os << "Move Joystick {id=" << e.joystickId << ", axis=" << e.axis << ", pos=" << e.position << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Joystick::Axis const& a) {
    switch(a) {
        case sf::Joystick::Axis::X:
            return os << "Axis X";
        case sf::Joystick::Axis::Y:
            return os << "Axis Y";
        case sf::Joystick::Axis::Z:
            return os << "Axis Z";
        case sf::Joystick::Axis::R:
            return os << "Axis R";
        case sf::Joystick::Axis::U:
            return os << "Axis U";
        case sf::Joystick::Axis::V:
            return os << "Axis V";
        case sf::Joystick::Axis::PovX:
            return os << "Axis PovX";
        case sf::Joystick::Axis::PovY:
            return os << "Axis PovY";
        default:
            return os << "Axis Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, sf::Event::KeyEvent const& e) { 
    return os << "Key {code=" << e.code << ", special=" << e.alt << "/" << e.control << "/" << e.shift << "/" << e.system << "}"; 
}

std::ostream& operator<<(std::ostream& os, sf::Keyboard::Key const& k) {
    switch(k) {
        case sf::Keyboard::Key::Unknown: return os << "Key Unknown";
        case sf::Keyboard::Key::A: return os << "Key A";
        case sf::Keyboard::Key::B: return os << "Key B";
        case sf::Keyboard::Key::C: return os << "Key C";
        case sf::Keyboard::Key::D: return os << "Key D";
        case sf::Keyboard::Key::E: return os << "Key E";
        case sf::Keyboard::Key::F: return os << "Key F";
        case sf::Keyboard::Key::G: return os << "Key G";
        case sf::Keyboard::Key::H: return os << "Key H";
        case sf::Keyboard::Key::I: return os << "Key I";
        case sf::Keyboard::Key::J: return os << "Key J";
        case sf::Keyboard::Key::K: return os << "Key K";
        case sf::Keyboard::Key::L: return os << "Key L";
        case sf::Keyboard::Key::M: return os << "Key M";
        case sf::Keyboard::Key::N: return os << "Key N";
        case sf::Keyboard::Key::O: return os << "Key O";
        case sf::Keyboard::Key::P: return os << "Key P";
        case sf::Keyboard::Key::Q: return os << "Key Q";
        case sf::Keyboard::Key::R: return os << "Key R";
        case sf::Keyboard::Key::S: return os << "Key S";
        case sf::Keyboard::Key::T: return os << "Key T";
        case sf::Keyboard::Key::U: return os << "Key U";
        case sf::Keyboard::Key::V: return os << "Key V";
        case sf::Keyboard::Key::W: return os << "Key W";
        case sf::Keyboard::Key::X: return os << "Key X";
        case sf::Keyboard::Key::Y: return os << "Key Y";
        case sf::Keyboard::Key::Z: return os << "Key Z";
        case sf::Keyboard::Key::Num0: return os << "Key Num0";
        case sf::Keyboard::Key::Num1: return os << "Key Num1";
        case sf::Keyboard::Key::Num2: return os << "Key Num2";
        case sf::Keyboard::Key::Num3: return os << "Key Num3";
        case sf::Keyboard::Key::Num4: return os << "Key Num4";
        case sf::Keyboard::Key::Num5: return os << "Key Num5";
        case sf::Keyboard::Key::Num6: return os << "Key Num6";
        case sf::Keyboard::Key::Num7: return os << "Key Num7";
        case sf::Keyboard::Key::Num8: return os << "Key Num8";
        case sf::Keyboard::Key::Num9: return os << "Key Num9";
        case sf::Keyboard::Key::Escape: return os << "Key Escape";
        case sf::Keyboard::Key::LControl: return os << "Key LControl";
        case sf::Keyboard::Key::LShift: return os << "Key LShift";
        case sf::Keyboard::Key::LAlt: return os << "Key LAlt";
        case sf::Keyboard::Key::LSystem: return os << "Key LSystem";
        case sf::Keyboard::Key::RControl: return os << "Key RControl";
        case sf::Keyboard::Key::RShift: return os << "Key RShift";
        case sf::Keyboard::Key::RAlt: return os << "Key RAlt";
        case sf::Keyboard::Key::RSystem: return os << "Key RSystem";
        case sf::Keyboard::Key::Menu: return os << "Key Menu";
        case sf::Keyboard::Key::LBracket: return os << "Key LBracket";
        case sf::Keyboard::Key::RBracket: return os << "Key RBracket";
        case sf::Keyboard::Key::Semicolon: return os << "Key Semicolon";
        case sf::Keyboard::Key::Comma: return os << "Key Comma";
        case sf::Keyboard::Key::Period: return os << "Key Period";
        case sf::Keyboard::Key::Quote: return os << "Key Quote";
        case sf::Keyboard::Key::Slash: return os << "Key Slash";
        case sf::Keyboard::Key::Backslash: return os << "Key Backslash";
        case sf::Keyboard::Key::Tilde: return os << "Key Tilde";
        case sf::Keyboard::Key::Equal: return os << "Key Equal";
        case sf::Keyboard::Key::Hyphen: return os << "Key Hyphen";
        case sf::Keyboard::Key::Space: return os << "Key Space";
        case sf::Keyboard::Key::Enter: return os << "Key Enter";
        case sf::Keyboard::Key::Backspace: return os << "Key Backspace";
        case sf::Keyboard::Key::Tab: return os << "Key Tab";
        case sf::Keyboard::Key::PageUp: return os << "Key PageUp";
        case sf::Keyboard::Key::PageDown: return os << "Key PageDown";
        case sf::Keyboard::Key::End: return os << "Key End";
        case sf::Keyboard::Key::Home: return os << "Key Home";
        case sf::Keyboard::Key::Insert: return os << "Key Insert";
        case sf::Keyboard::Key::Delete: return os << "Key Delete";
        case sf::Keyboard::Key::Add: return os << "Key Add";
        case sf::Keyboard::Key::Subtract: return os << "Key Subtract";
        case sf::Keyboard::Key::Multiply: return os << "Key Multiply";
        case sf::Keyboard::Key::Divide: return os << "Key Divide";
        case sf::Keyboard::Key::Left: return os << "Key Left";
        case sf::Keyboard::Key::Right: return os << "Key Right";
        case sf::Keyboard::Key::Up: return os << "Key Up";
        case sf::Keyboard::Key::Down: return os << "Key Down";
        case sf::Keyboard::Key::Numpad0: return os << "Key Numpad0";
        case sf::Keyboard::Key::Numpad1: return os << "Key Numpad1";
        case sf::Keyboard::Key::Numpad2: return os << "Key Numpad2";
        case sf::Keyboard::Key::Numpad3: return os << "Key Numpad3";
        case sf::Keyboard::Key::Numpad4: return os << "Key Numpad4";
        case sf::Keyboard::Key::Numpad5: return os << "Key Numpad5";
        case sf::Keyboard::Key::Numpad6: return os << "Key Numpad6";
        case sf::Keyboard::Key::Numpad7: return os << "Key Numpad7";
        case sf::Keyboard::Key::Numpad8: return os << "Key Numpad8";
        case sf::Keyboard::Key::Numpad9: return os << "Key Numpad9";
        case sf::Keyboard::Key::F1: return os << "Key F1";
        case sf::Keyboard::Key::F2: return os << "Key F2";
        case sf::Keyboard::Key::F3: return os << "Key F3";
        case sf::Keyboard::Key::F4: return os << "Key F4";
        case sf::Keyboard::Key::F5: return os << "Key F5";
        case sf::Keyboard::Key::F6: return os << "Key F6";
        case sf::Keyboard::Key::F7: return os << "Key F7";
        case sf::Keyboard::Key::F8: return os << "Key F8";
        case sf::Keyboard::Key::F9: return os << "Key F9";
        case sf::Keyboard::Key::F10: return os << "Key F10";
        case sf::Keyboard::Key::F11: return os << "Key F11";
        case sf::Keyboard::Key::F12: return os << "Key F12";
        case sf::Keyboard::Key::F13: return os << "Key F13";
        case sf::Keyboard::Key::F14: return os << "Key F14";
        case sf::Keyboard::Key::F15: return os << "Key F15";
        case sf::Keyboard::Key::Pause: return os << "Key Pause";
        default: return os << "Key Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, sf::Event::MouseButtonEvent const& e) { 
    return os << "Mouse Button {but=" << e.button << ", pos=" << sf::Vector2i(e.x, e.y) << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Mouse::Button const& b) {
    switch(b) {
        case sf::Mouse::Button::Left:
            return os << "Button Left";
        case sf::Mouse::Button::Right:
            return os << "Button Right";
        case sf::Mouse::Button::Middle:
            return os << "Button Middle";
        case sf::Mouse::Button::XButton1:
            return os << "Button XButton1";
        case sf::Mouse::Button::XButton2:
            return os << "Button XButton2";
        default:
            return os << "Button Unknown";
    }
} 

std::ostream& operator<<(std::ostream& os, sf::Event::MouseMoveEvent const& e) { 
    return os << "Move Mouse {pos=" << sf::Vector2i(e.x, e.y) << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Event::MouseWheelScrollEvent const& e) { 
    return os << "Scroll Mouse Wheel {delta=" << e.delta << ", pos=" << sf::Vector2i(e.x, e.y) << ", wheel=" << e.wheel << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Mouse::Wheel const& w) { 
    switch(w) {
        case sf::Mouse::Wheel::VerticalWheel:
            return os << "Wheel VerticalWheel";
        case sf::Mouse::Wheel::HorizontalWheel:
            return os << "Wheel HorizontalWheel";
        default:
            return os << "Wheel Unknown";
    }
}
std::ostream& operator<<(std::ostream& os, sf::Event::SensorEvent const& e) { 
    return os << "Sensor {type=" << e.type << ", axis=" << sf::Vector3f(e.x, e.y, e.z) << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Sensor::Type const& s) { 
    switch(s) {
        case sf::Sensor::Type::Accelerometer:
            return os << "Sensor Accelerometer";
        case sf::Sensor::Type::Gyroscope:
            return os << "Sensor Gyroscope";
        case sf::Sensor::Type::Magnetometer:
            return os << "Sensor Magnetometer";
        case sf::Sensor::Type::Gravity:
            return os << "Sensor Gravity";
        case sf::Sensor::Type::UserAcceleration:
            return os << "Sensor UserAcceleration";
        case sf::Sensor::Type::Orientation:
            return os << "Sensor Orientation";
        default:
            return os << "Sensor Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, sf::Event::SizeEvent const& e) { 
    return os << "Resize {h=" << e.height << ", w=" << e.width << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Event::TextEvent const& e) { 
    return os << "Text {unicode=" << e.unicode << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Event::TouchEvent const& e) { 
    return os << "Touch {finger=" << e.finger << ", pos=" << sf::Vector2i(e.x, e.y) << "}";
}

std::ostream& operator<<(std::ostream& os, sf::Font::Info const& f) { 
    return os << "Info {family=" << f.family << "}";
}

}