//assignment 7
//Hermione Warr
//16/03/2020

#include<iostream>

class vector 
{
	friend std::ostream& operator<<(std::ostream& os, const vector& out_vector);
	friend std::istream& operator>>(std::istream& is, vector& vector_in);
private:
	double x_comp{0};
	double y_comp{0};
	double z_comp{0};
protected:
public:
	//default and parameterised constructors and destructors
	vector() = default;
	vector(double x_component, double y_component, double z_component) 
	{
		x_comp = x_component; y_comp = y_component; z_comp = z_component;
	}
	~vector() {std::cout << "destructor called" << std::endl;};//do i need to delete anything?
	//move and copy constructors and assingment operators
	vector(vector&);
	vector(vector&&) noexcept;
	vector& operator=(vector&);
	vector& operator=(vector&&) noexcept;
	//accessors returning components of a vector and its length
	size_t get_x_comp()const { return x_comp; }
	size_t get_y_comp()const { return y_comp; }
	size_t get_z_comp()const { return z_comp; }
	double vector_length() const{
		double length{};
		return length = sqrt(pow(x_comp,2) + pow(y_comp,2) + pow(z_comp,2));
	}

};
/*--------------------------
member functions of vector
---------------------------*/
//overload friend operators for output and input stream
std::ostream& operator<<(std::ostream& os, const vector &out_vector)
{
	if (out_vector.y_comp > 0){
		if (out_vector.z_comp > 0) {
			os << out_vector.x_comp << "x + " << out_vector.y_comp << "y + " << out_vector.z_comp << "z\n";
		}
		else {
			os << out_vector.x_comp << "x + " << out_vector.y_comp << "y " << out_vector.z_comp << "z\n";
		}
	}
	else if (out_vector.y_comp < 0) {
		if (out_vector.z_comp > 0) {
			os << out_vector.x_comp << "x " << out_vector.y_comp << "y + " << out_vector.z_comp << "z\n";
		}
		else {
			os << out_vector.x_comp << "x " << out_vector.y_comp << "y " << out_vector.z_comp << "z\n";
		}
	}
	return os;
}
std::istream& operator>>(std::istream& is, vector& vector_in) {
	std::cout << "please enter your cartesian vector as x comp y_comp zcomp seperated by a space: " << std::endl;
	is >> vector_in.x_comp >> vector_in.y_comp >> vector_in.z_comp;
	return is;
}
//copy and move constructors and operators
vector::vector(vector& copy_vector) 
{
	std::cout << "copy constructor called" << std::endl;
	x_comp = copy_vector.x_comp;
	y_comp = copy_vector.y_comp;
	z_comp = copy_vector.z_comp;
}
vector::vector(vector&& move_vector) noexcept
{
	std::cout << "move constructor called" << std::endl;
	x_comp = move_vector.x_comp;
	y_comp = move_vector.y_comp;
	z_comp = move_vector.z_comp;
	move_vector.x_comp = 0; move_vector.y_comp = 0; move_vector.z_comp = 0;
}
vector& vector::operator=(vector& copyvector)
{
	std::cout << "copy assignment operator called \n";
	if (&copyvector == this) return *this;
	x_comp = 0; y_comp = 0; z_comp = 0;
	x_comp = copyvector.x_comp; y_comp = copyvector.y_comp; z_comp = copyvector.z_comp;
	return *this;
}
vector& vector::operator=(vector&& movevector) noexcept
{
	std::cout << "move aasingment operator called" << std::endl;
	std::swap(x_comp, movevector.x_comp);
	std::swap(y_comp, movevector.y_comp);
	std::swap(z_comp, movevector.z_comp);
	return *this;
}


class four_vector:public vector
{
private:

public:

};

class particle
{
private:
public:
};

int main() {
	vector default_example;
	std::cout << "default constructor:" << default_example;
	vector paramertised_eg{2,-3,1};
	std::cout << "parameterised vector: " << paramertised_eg;
	std::cout << "vector length: " << paramertised_eg.vector_length() << std::endl;
	return 0;
}