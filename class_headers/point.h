#ifndef POINT_H
#define POINT_H

class point
{
private:
    int x, y;
public:
    point();

    //setter functions
    void set(int x, int y);
    void setX(int x);
    void setY(int y);

    //getter functions
    int getX();
    int getY();


    //helper function
    void print() const;

};

#endif // POINT_H
