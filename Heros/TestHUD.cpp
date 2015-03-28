#include "TestHUD.h"
void TestHUD::update(GameScene *scene , double delta, Keys keys) {

}
void TestHUD::render(HDC gr) {
    TextOut(gr, 200, 10, "This is the HUD HUD HUD", 23);
}