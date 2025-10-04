// these functions are implemented in javascript
namespace js {
    extern "C" {
    void alert(const char* msg);
    void console_log(const char* msg);
    void goto_link(const char* msg);
    void open_link(const char* msg);
    }
}
