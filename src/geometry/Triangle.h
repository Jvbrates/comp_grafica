//
// Created by jvbrates on 4/22/24.
//

#ifndef COMP_GRAFICA_TRIANGLE_H
#define COMP_GRAFICA_TRIANGLE_H


class Triangle {
public:
    double getSide1() const;

    void setSide1(double side1);

    double getSide2() const;

    void setSide2(double side2);

    double getSide3() const;

    void setSide3(double side3);

    double getAngle1() const;

    void setAngle1(double angle1);

    double getAngle2() const;

    void setAngle2(double angle2);

    double getAngle3() const;

    void setAngle3(double angle3);

    void solve();
    bool control[6] = {false, false, false, false, false, false};
protected:
    double angle1, angle2, angle3;
    double side1, side2, side3;



};


#endif //COMP_GRAFICA_TRIANGLE_H
