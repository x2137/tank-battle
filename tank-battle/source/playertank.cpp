#include "../include/playertank.h"
#include "../include/utils.h"
#include <iostream>

using std::cout;


PlayerTank::PlayerTank(short x, short y, short h, short w, Direction d, const std::string &who, short blood, short life, bool attack, short speed, short pattern) : Tank(x, y, h, w, d, blood, life, attack, speed) {
    this->pattern = pattern;
    this->who = who;
}

void PlayerTank::changePattern(short new_pattern) {
    this->pattern = new_pattern;
}

void PlayerTank::showUp() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->pattern) {
    case 0:  // 没吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "  " << "︽" << "  ";
        Utils::setCursorPosition(left, top + 1);
        cout << "【" << "  " << "】";
        Utils::setCursorPosition(left, top + 2);
        cout << "■" << "  " << "■";
        break;
    case 1:  // 吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "  " << "︽" << "  ";
        Utils::setCursorPosition(left, top + 1);
        cout << "【" << "■" << "】";
        Utils::setCursorPosition(left, top + 2);
        cout << "■" << "■" << "■";
        break;
    }
}

void PlayerTank::showDown() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->pattern) {
    case 0:  // 没吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "■" << "  " << "■";
        Utils::setCursorPosition(left, top + 1);
        cout << "【" << "  " << "】";
        Utils::setCursorPosition(left, top + 2);
        cout << "  " << "︾" << "  ";
        break;
    case 1:  // 吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "■" << "■" << "■";
        Utils::setCursorPosition(left, top + 1);
        cout << "【" << "■" << "】";
        Utils::setCursorPosition(left, top + 2);
        cout << "  " << "︾" << "  ";
        break;
    }
}

void PlayerTank::showLeft() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->pattern) {
    case 0:  // 没吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "  " << "︻" << "■";
        Utils::setCursorPosition(left, top + 1);
        cout << "《" << "  " << "  ";
        Utils::setCursorPosition(left, top + 2);
        cout << "  " << "︼" << "■";
        break;
    case 1:  // 吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "  " << "︻" << "■";
        Utils::setCursorPosition(left, top + 1);
        cout << "《" << "■" << "■";
        Utils::setCursorPosition(left, top + 2);
        cout << "  " << "︼" << "■";
        break;
    }
}

void PlayerTank::showRight() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->pattern) {
    case 0:  // 没吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "■" << "︻" << "  ";
        Utils::setCursorPosition(left, top + 1);
        cout << "  " << "  " << "》";
        Utils::setCursorPosition(left, top + 2);
        cout << "■" << "︼" << "  ";
        break;
    case 1:  // 吃到增强剂
        Utils::setCursorPosition(left, top);
        cout << "■" << "︻" << "  ";
        Utils::setCursorPosition(left, top + 1);
        cout << "■" << "■" << "》";
        Utils::setCursorPosition(left, top + 2);
        cout << "■" << "︼" << "  ";
        break;
    }
}

void PlayerTank::setMyScore(short enemy_type) {
    switch (enemy_type) {
    case 0:
        this->score += 100;
        break;
    case 1:  // 这种类别的暂时没有实现
        this->score += 150;
        break;
    case 2:  // 这种类别的暂时没有实现
        this->score += 200;
        break;
    }
}

void PlayerTank::initializeBloodVolume() {
    this->blood_volume = 150;
}

int PlayerTank::getMyScore() const {
    return this->score;
}

short PlayerTank::getMyPattern() {
    return this->pattern;
}

std::string PlayerTank::getMyName() {
    return this->who;
}
