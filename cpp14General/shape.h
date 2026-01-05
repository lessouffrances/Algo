class Shape 
{
    public:
    virtual double area() const = 0;
};

class Circle : public Shape 
{
    public:
    Circle(double radius) : _radius{radius} {}
    
    double area() const override {
        return 3.14 * _radius * _radius;
    }
    private:
    double _radius;
}

int main() 
{
    Circle c(5.0);

}