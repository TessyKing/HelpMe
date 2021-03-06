#include "qwidgetdraw.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>


int ecgWave[] = {
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2008, 2016, 2016, 2016, 2024, 2032, 2048,
    2064, 2064, 2064, 2072, 2080, 2080, 2080, 2088, 2096, 2104,
    2112, 2112, 2112, 2112, 2112, 2112, 2104, 2096, 2088,
    2080, 2080, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2032,
    2032, 2016, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 1992, 1984, 1976,
    1968, 1960, 1952, 1944, 1936, 1944, 1952, 2016, 2080, 2136,
    2192, 2256, 2320, 2376, 2432, 2488, 2544, 2568, 2592, 2536,
    2480, 2424, 2368, 2304, 2240, 2184, 2128, 2072, 2016, 1968,
    1920, 1928, 1936, 1944, 1952, 1960, 1968, 1984, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2008, 2016, 2024, 2032, 2032,
    2032, 2048, 2064, 2064, 2064, 2072, 2080, 2088, 2096, 2104,
    2112, 2112, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2160,
    2160, 2160, 2160, 2168, 2176, 2176, 2176, 2184, 2192,
    2192, 2192, 2192, 2200, 2208, 2208, 2208, 2208, 2208, 2208,
    2208, 2200, 2192, 2192, 2192, 2184, 2176, 2176, 2176, 2168,
    2160, 2160, 2160, 2144, 2128, 2128, 2128, 2128, 2128, 2112,
    2096, 2088, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2024,
    2016, 2016, 2016, 2008, 2000, 2000, 2000, 2000, 2000,
    2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
};

QWidgetDraw::QWidgetDraw(QWidget *parent) : QWidget(parent) {
    this->resize(1600, 500);

    this->map = new QPixmap(this->width(), this->height());
    this->map->fill(Qt::black);

    this->timer = new QTimer(parent);
    this->timer->start(10); //???????????????

//    connect(timer, &QTimer::timeout, this, &QWidgetDraw::refresh);
    connect(timer, &QTimer::timeout, this, &QWidgetDraw::sendData);

    connect(this, &QWidgetDraw::rxDataSignal, this, &QWidgetDraw::refreshFromData);
    connect(this, &QWidgetDraw::rxDataSignal, this, &QWidgetDraw::testRx);
}

void QWidgetDraw::testRx(int data) {
    qDebug() << "rx:" << data;
}

void QWidgetDraw::sendData() {
    int data = 0;
    int height = this->height();

    data = height - ecgWave[index] * height / 4096;

    this->index += 3;

    if(this->index >= sizeof(ecgWave) / sizeof(int)) {
        this->index = 0;
    }

    emit rxDataSignal(data);
}

void QWidgetDraw::refreshFromData(int data) {
    // ??????????????????
    QPainter *painter = new QPainter();
    painter->begin(this->map);

    //????????????
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::green);
    painter->setPen(*pen);

    // ?????????map????????????
    this->drawWave(painter, data);
    painter->end();

    // ??????update?????????paintevent??????
    this->update();
}

void QWidgetDraw::refresh() {
    // ??????????????????
    QPainter *painter = new QPainter();
    painter->begin(this->map);
    // ?????????map????????????
    this->draw(painter);
    painter->end();

    // ??????update?????????paintevent??????
    this->update();
}

// ????????????
void QWidgetDraw::paintEvent(QPaintEvent *event) {
    QPainter *painter = new QPainter();

    painter->begin(this);
    // ???????????????
    painter->drawPixmap(0, 0, *this->map);
    painter->end();
}

void QWidgetDraw::drawDemo(QPainter *painter) {
    QPen *pen = new QPen();
    //????????????
    pen->setColor(Qt::green);

    //????????????
    painter->save();
    painter->setPen(*pen);
    //??????
    painter->drawRect(0, 0, 100, 100);
    // todo ??????????????????
    // ????????????????????????
    painter->restore();
}

void QWidgetDraw::draw(QPainter *painter) {
    //????????????
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::green);
    painter->setPen(*pen);

//    drawTriangleNew(painter);
    drawWaveFromArray(painter);
}


void QWidgetDraw::drawTriangleNew(QPainter *painter) {
    int width = this->width();
    int height = this->height();

    // ????????????
    QPen *pen = new QPen();
    // ????????????
    pen->setWidth(4);
    pen->setColor(Qt::black);

    // ????????????
    painter->save();
    // ????????????
    painter->setPen(*pen);

    // ??????
    painter->drawLine(x, 0, x, height);
    // ????????????
    painter->restore();

    painter->drawPoint(x, height - y);
    x += 1;

    if(0 == dir) {
        y += 1;
        if(y > height / 2) {
            dir = 1;
        }
    } else {
        y -= 1;
        if(0 == y) {
            dir = 0;
        }
    }

    if(x >= width) {
        x = 0;
    }
}

void QWidgetDraw::drawTriangle(QPainter *painter) {
    int width = this->width();
    int height = this->height();
    int cnt;
    int x, y;
    int dir = 0;

    x = 0;
    y = 0;
    for(cnt = 0; cnt < width; cnt ++) {
        painter->drawPoint(x, height - y);
        x += 1;

        if(0 == dir) {
            y += 1;
            if(y > height / 2) {
                dir = 1;
            }
        } else {
            y -= 1;
            if(0 == y) {
                dir = 0;
            }
        }
    }
}



void QWidgetDraw::drawWaveFromArray(QPainter *painter) {
    int data = 0;
    int height = this->height();

    data = height - ecgWave[index] * height / 4096;
    this->drawWave(painter, data);

    this->index += 3;

    if(this->index >= sizeof(ecgWave) / sizeof(int)) {
        this->index = 0;
    }
}


void QWidgetDraw::drawWave(QPainter *painter, int data) {
    int width = this->width();
    int height = this->height();

    // ????????????
    QPen *pen = new QPen();
    // ????????????
    pen->setWidth(6);
    pen->setColor(Qt::black);

    // ????????????
    painter->save();
    // ????????????
    painter->setPen(*pen);

    // ??????
    painter->drawLine(this->x + 2, 0, this->x + 2, height);
    // ????????????
    painter->restore();

//    painter->drawPoint(this->x, data);
    painter->drawLine(this->x - 1, lastData, this->x, data);
    lastData = data;

    // ?????????
    this->x += 1;

    if(this->x >= width) {
        this->x = 0;
    }
}

