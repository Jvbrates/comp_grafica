//
// Created by jvbrates on 4/22/24.
//

#include "Triangle.h"
#include "math.h"

double Triangle::getSide1() const {
    return side1;

}

void Triangle::setSide1(double side1) {
    this->control[0] = true;
    Triangle::side1 = side1;
}

double Triangle::getSide2() const {
    return side2;
}

void Triangle::setSide2(double side2) {
    this->control[1] = true;
    Triangle::side2 = side2;
}

double Triangle::getSide3() const {
    return side3;
}

void Triangle::setSide3(double side3) {
    this->control[2] = true;
    Triangle::side3 = side3;
}

double Triangle::getAngle1() const {
    return angle1;
}

void Triangle::setAngle1(double angle1) {
    this->control[3] = true;
    Triangle::angle1 = angle1;
}

double Triangle::getAngle2() const {
    return angle2;
}

void Triangle::setAngle2(double angle2) {
    this->control[4] = true;
    Triangle::angle2 = angle2;
}

double Triangle::getAngle3() const {
    return angle3;
}

void Triangle::setAngle3(double angle3) {
    this->control[5] = true;
    Triangle::angle3 = angle3;
}

void Triangle::solve() {
    // Se três lados foram fornecidos
    if (control[0] && control[1] && control[2]) {
        // Usando a lei dos cossenos para encontrar os ângulos
        angle1 = acos((side2*side2 + side3*side3 - side1*side1) / (2 * side2 * side3));
        angle2 = acos((side1*side1 + side3*side3 - side2*side2) / (2 * side1 * side3));
        angle3 = acos((side1*side1 + side2*side2 - side3*side3) / (2 * side1 * side2));

        control[3] = true;
        control[4] = true;
        control[5] = true;
    }
        // Se dois lados e um ângulo oposto foram fornecidos
    else if ((control[0] && control[1] && control[4]) ||
             (control[0] && control[2] && control[3]) ||
             (control[1] && control[2] && control[5])) {
        // Usando a lei dos senos para encontrar o lado e os ângulos restantes
        if (control[0]) {
            side1 = side2 * sin(angle1) / sin(angle2);
            side3 = side2 * sin(angle3) / sin(angle2);
        } else if (control[1]) {
            side2 = side1 * sin(angle2) / sin(angle1);
            side3 = side1 * sin(angle3) / sin(angle1);
        } else if (control[2]) {
            side3 = side1 * sin(angle3) / sin(angle1);
            side2 = side1 * sin(angle2) / sin(angle1);
        }

        control[3] = true;
        control[4] = true;
        control[5] = true;
    }
        // Se dois ângulos e um lado foram fornecidos
    else if ((control[3] && control[4] && control[5]) ||
             (control[3] && control[1] && control[2]) ||
             (control[4] && control[0] && control[2])) {
        // Usando a lei dos senos para encontrar os lados restantes
        if (control[3]) {
            side2 = side1 * sin(angle2) / sin(angle1);
            side3 = side1 * sin(angle3) / sin(angle1);
        } else if (control[4]) {
            side1 = side2 * sin(angle1) / sin(angle2);
            side3 = side2 * sin(angle3) / sin(angle2);
        } else if (control[5]) {
            side1 = side3 * sin(angle1) / sin(angle3);
            side2 = side3 * sin(angle2) / sin(angle3);
        }

        control[0] = true;
        control[1] = true;
        control[2] = true;
    }
}
