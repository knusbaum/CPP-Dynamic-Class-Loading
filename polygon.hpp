#ifndef POLYGON_H
#define POLYGON_H

class Polygon {
protected:
    double side_length_;

public:
    Polygon(int length)
        : side_length_(length) {}

    virtual ~Polygon() {}

    void set_side_length(double side_length) {
        side_length_ = side_length;
    }

    virtual double area() const = 0;

    typedef Polygon * create_t(int);
    typedef void destroy_t(Polygon *);

};

#endif
