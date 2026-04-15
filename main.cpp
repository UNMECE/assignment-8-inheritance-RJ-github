#include <iostream>
#include <cmath>
using namespace std;

class Field
{
protected:
    double *value;

public:
    Field()
    {
        value = new double[3]{0.0, 0.0, 0.0};
    }

    Field(double x, double y, double z)
    {
        value = new double[3]{x, y, z};
    }

    Field(const Field &other)
    {
        value = new double[3];
        for (int i = 0; i < 3; i++)
            value[i] = other.value[i];
    }

    Field &operator=(const Field &other)
    {
        if (this != &other)
        {
            delete[] value;
            value = new double[3];
            for (int i = 0; i < 3; i++)
                value[i] = other.value[i];
        }
        return *this;
    }

    virtual ~Field()
    {
        delete[] value;
    }

    void printMagnitude()
    {
        double mag = sqrt(value[0]*value[0] +
                          value[1]*value[1] +
                          value[2]*value[2]);

				cout << "Magnitude: " << mag << endl;
		}

		void printComponents()
		{
			cout << "(" 
				<< value[0] << ", "
				<< value[1] << ", "
				<< value[2] << ")\n";
		}
};

class Electric_Field : public Field
{
private:
    double computed_E;

public:
    Electric_Field() : Field() {}
    Electric_Field(double x, double y, double z) : Field(x,y,z) {}

    Electric_Field(const Electric_Field &other) : Field(other)
    {
        computed_E = other.computed_E;
    }

    void calculateField(double Q, double r)
    {
        const double epsilon0 = 8.854e-12;
        computed_E = Q / (4 * M_PI * r * r * epsilon0);
    }

    void printComputedField()
    {
        cout << "Computed Electric Field: " << computed_E << endl;
    }

    Electric_Field operator+(const Electric_Field &other)
    {
        return Electric_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }

    friend ostream &operator<<(ostream &os, const Electric_Field &e)
    {
        os << "(" << e.value[0] << ", "
           << e.value[1] << ", "
           << e.value[2] << ")";
        return os;
    }
};

class Magnetic_Field : public Field
{
private:
    double computed_B;

public:
    Magnetic_Field() : Field() {}
    Magnetic_Field(double x, double y, double z) : Field(x,y,z) {}

    Magnetic_Field(const Magnetic_Field &other) : Field(other)
    {
        computed_B = other.computed_B;
    }

    void calculateField(double I, double r)
    {
        const double mu0 = 4 * M_PI * 1e-7;
        computed_B = I / (2 * M_PI * r * mu0);
    }

    void printComputedField()
    {
        cout << "Computed Magnetic Field: " << computed_B << endl;
    }

    Magnetic_Field operator+(const Magnetic_Field &other)
    {
        return Magnetic_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }

    friend ostream &operator<<(ostream &os, const Magnetic_Field &b)
    {
        os << "(" << b.value[0] << ", "
           << b.value[1] << ", "
           << b.value[2] << ")";
        return os;
    }
};

int main()
{
    Electric_Field E(0, 1e5, 1e3);
    Magnetic_Field B(2.0, 3.0, 4.0);

    cout << "Electric Field:\n";
    E.printMagnitude();

    cout << "\nMagnetic Field:\n";
    B.printMagnitude();

    E.calculateField(1e-6, 0.05); // Q, r
    B.calculateField(5.0, 0.02);  // I, r

    cout << "\nPhysics Calculations:\n";
    E.printComputedField();
    B.printComputedField();

    Electric_Field e1(1,2,3), e2(4,5,6), e3;
    e3 = e1 + e2;

    Magnetic_Field b1(1,1,1), b2(2,2,2), b3;
    b3 = b1 + b2;

    cout << "\nElectric Field Addition:\n";
		e1.printComponents();
		e2.printComponents();
    cout << "e1 + e2 = " << e3 << endl;

    cout << "\nMagnetic Field Addition:\n";
		b1.printComponents();
		b2.printComponents();
    cout << "b1 + b2 = " << b3 << endl;

    return 0;
}
