//
// Created by dudu233 on 2024/6/11.
//

#include "game.h"
#include "debug.h"
#include "easyx.h"
#include "graphics.h"
#include "resource.h"
#include "window.h"

IMAGE tmp_4;
game::game(unsigned short level, Difficulty diff) : level(level), difficulty(diff), score(0), time(10), moles(0), destroyed(false) {
    initWindow();
    // ����ͼƬ��Դ
    initResource();
    getimage(&tmp_4, 160, 0, 100, 120);
    // ���ɵ��󶴺͵���
    spawnHoles();
    moleThread = new std::thread(&game::spawnMoles, this);
    hitThread = new std::thread(&game::hitListener, this);

    // ���ٴ���
    hammerThread = new std::thread(&game::hammerListener, this);
    // ����ˢ��
    scoreThread = new std::thread(&game::scoreListener, this);
    // �ؿ�����
    endThread = new std::thread(&game::endListener, this);
}

game::~game() {
    destroy();
}

void initWindow() {
    // ������ϷͼƬ
    IMAGE img;
    loadimage(&img, getPic("game").c_str(), 800, 600);
    putimage(0, 0, &img);
    // ���ص�ǰ�ؿ����÷֣����ط���
    // ��ǰ�ؿ�
    settextcolor(WHITE);
    settextstyle(30, 0, _T("����"));
    outtextxy(10, 10, "��ǰ�ؿ�:");
    // ���ط���
    settextstyle(30, 0, _T("����"));
    outtextxy(10, 50, "ʣ��ʱ��:");
    // ��ǰ�÷�
    settextstyle(30, 0, _T("����"));
    outtextxy(10, 90, "��ǰ����:");
    // ��ǰ�Ѷ�
    settextstyle(30, 0, _T("����"));
    outtextxy(10, 130, "��ǰ�Ѷ�:");
}

// ���ݹؿ��ȼ����ѶȻ���Ѷ�����
float game::getDifficultyFactor() {
    float factor = this->level;
    if (factor > 100) {
        factor /= 4.0F;
    } else if (factor > 50) {
        factor /= 3.0F;
    } else if (factor > 30) {
        factor /= 2.5F;
    } else if (factor > 20) {
        factor /= 2.0F;
    } else if (factor > 10) {
        factor /= 1.5F;
    } else if (factor > 5) {
        factor /= 1.3F;
    } else {
        factor /= 1.1F;
    }
    switch (this->difficulty) {
        case EASY:
            return factor * 0.8F;
        case NORMAL:
            return factor * 1.0F;
        case HARD:
            return factor * 1.3F;
        default:
            return -1;
    }
}

// ��ʼ������
void game::spawnHoles() {
    float diff = getDifficultyFactor();// ��ȡ�Ѷ�����
    // �����Ѷȼ�������
    unsigned int rows = 1 + (int) (diff / 5.0F);
    unsigned int cols = rows;
    unsigned int gapX = 40;
    unsigned int gapY = 30;

    for (int i = 0; i < rows; i++) {
        std::vector<Hole> hole(cols);
        holes.push_back(hole);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = WINDOW_WIDTH / 2 - (rows * 100 + (rows - 1) * gapX) / 2 + i * (100 + gapX);
            int y = WINDOW_HEIGHT / 2 - (cols * 50 + (cols - 1) * gapY) / 2 + j * (50 + gapY);
            putImage(x, y, IMG_HOLE);
            holes[i][j] = {x, y, 100, 50, mole(x + 30, y)};
        }
    }
}

// ������ɵ���
void game::spawnMoles() {
    MOUSEMSG m;
    int x, y;
    while (!destroyed) {
        for (auto &row: holes) {
            for (auto &hole: row) {
                if (rand() < (int) (getDifficultyFactor() * 100.0F)) {
                    debug("show mole");
                    hole.mole.show();
                }
            }
        }
        delay(50);
    }
}

// ������ɵ���
void game::hitListener() {
    MOUSEMSG m;
    int x, y;
    while (!destroyed) {
        m = mouseMessage();
        x = m.x;
        y = m.y;
        for (auto &row: holes) {
            for (auto &hole: row) {
                if (m.mkLButton && hole.mole.isHited(x, y)) {
                    debug("mole hited, now score:" + std::to_string(this->score));
                    // ÿ����һ�������5��
                    score += 5;
                }
            }
        }
        delay(10);
    }
}

// ��������λ��
void game::hammerListener() {
    IMAGE *tmp;
    MOUSEMSG m;
    int x, y, last_x, last_y;
    while (!destroyed) {
        m = mouseMessage();
        x = m.x - 50;
        y = m.y - 50;

        // ��ԭ֮ǰ��״̬
        if (tmp == nullptr) {
            tmp = new IMAGE;
        } else {
            putimage(last_x, last_y, tmp);
        }
        // ����֮ǰ��״̬
        getimage(tmp, x, y, 100, 100);
        last_x = x;
        last_y = y;
        // ���ô���
        if (m.mkLButton) {
            debug("hammer down.");
            putImage(x, y, IMG_HAMMER_DOWN);
        } else {
            putImage(x, y, IMG_HAMMER);
        }

        delay(10);
    }
}

// ����������ʾ
void game::scoreListener() {
    while (!destroyed) {
        putimage(160, 0, &tmp_4);
        switch (this->difficulty) {
            case EASY: {
                settextstyle(30, 0, "����");
                settextcolor(BLACK);
                outtextxy(160, 130, "��");
                break;
            }
            case NORMAL: {
                settextstyle(30, 0, "����");
                settextcolor(BLACK);
                outtextxy(160, 130, "��ͨ");
                break;
            }
            case HARD: {
                settextstyle(30, 0, "����");
                settextcolor(BLACK);
                outtextxy(160, 130, "����");
                break;
            }
        }// �����ǰ�ؿ�
        settextstyle(30, 0, "����");
        settextcolor(BLACK);
        outtextxy(160, 10, std::to_string(this->level).c_str());
        // ���ʣ��ʱ��
        settextstyle(30, 0, "����");
        settextcolor(BLACK);
        outtextxy(160, 50, std::to_string(this->time).c_str());
        // �����ǰ�÷�
        settextstyle(30, 0, "����");
        settextcolor(BLACK);
        outtextxy(160, 90, std::to_string(this->score).c_str());
        // ÿ��100msˢ��һ��
        delay(100);
    }
}


// ��Ϸʱ��
void game::endListener() {
    while (!destroyed) {
        // ÿ1s���һ��
        delay(1000);
        this->time--;
        debug("now time:" + std::to_string(this->time));
        if (time == 0) {
            // ���ؽ�����
            debug("level: " + std::to_string(this->level) + "ended");
            destroy();
            new game(++this->level, this->difficulty);
            break;
        }
    }
}

// ��ʼ�¹ؿ�
void game::startNewLevel() {
    increaseLevel();
    spawnMoles();
}

// ��ȡ��ǰ�÷�
unsigned int game::getScore() const {
    return score;
}

// ��ȡ��ǰ�ؿ��ȼ�
unsigned short game::getLevel() const {
    return level;
}

// ���ӹؿ��ȼ�
void game::increaseLevel() {
    ++level;
}

void game::destroy() {
    this->destroyed = true;
    for (auto &row: holes) {
        for (auto &hole: row) {
            hole.mole.destroy();
        }
    }
    // �ȴ������߳̽��� ����endThread
    if (moleThread && moleThread->joinable()) {
        moleThread->join();
    }
    if (hitThread && hitThread->joinable()) {
        hitThread->join();
    }
    if (hammerThread && hammerThread->joinable()) {
        hammerThread->join();
    }
    if (scoreThread && scoreThread->joinable()) {
        scoreThread->join();
    }
}
