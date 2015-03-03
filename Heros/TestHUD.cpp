#include "TestHUD.h"

void TestHUD::Update(GameScene *scene , double delta, Keys keys) {

}
void TestHUD::Render(HDC gr) {
    TextOut(gr, 5, 40, "Test", 4);
}