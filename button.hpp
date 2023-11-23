#ifndef BUTTON_HPP
#define BUTTON_HPP
namespace component {

class button {
public:
    button( int push_port, int light_port, bool interruptDriven );
    ~button();

    void setLight( bool on );
    bool isPushed( void );
private:
    int port_button;
    int port_light;
    bool interrupt;
};

}
#endif