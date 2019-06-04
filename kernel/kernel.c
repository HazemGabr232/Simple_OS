#include "../drivers/screen.h"

void main() {

    clear_screen();
    kprint_at("Does anybody want coffee?", 20, 5);
    kprint("!!!");
    kprint("\n\nWho wants coffee?");
    kprint_at(" I just made cawfee, Who wants cawffay?", 20, 9);
    kprint_at("test error", 88, 88);
}
