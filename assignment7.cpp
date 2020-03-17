//assignment 7
//Hermione Warr
//16/03/2020

#include<iostream>

class vector 
{
	friend std::ostream& operator<<(std::ostream& os, const vector& out_vector);
	friend std::istream& operator>>(std::istream& is, vector& vector_in);
private:
	double* vector_array{ nullptr };
	size_t vector_length{};
protected:
public:
	//default and parameterised constructors and destructors
	vector() = default;
	vector(size_t length) {
		vector_length = length;
		vector_array = new double[vector_length];
		for (int i{}; i < vector_length; i++) {
			vector_array[i] = 0;
		}
	}
	~vector() {std::cout << "destructor called" << std::endl;};//do i need to delete anything?
	double& operator[](size_t i) const;
	//move and copy constructors and assingment operators
	vector(vector&);
	vector(vector&&) noexcept;
	vector& operator=(vector&);
	vector& operator=(vector&&) noexcept;
	//accessors returning components of a vector and its length
	double length() const { return vector_length; }
	//dot product
	double dot_product(vector& dottie_boi);
};
/*--------------------------
member functions of vector
---------------------------*/
//overload friend operators for output and input stream
std::ostream& operator<<(std::ostream& os, const vector &out_vector)
{
	for (int i{}; i < out_vector.vector_length; i++) {
		os << out_vector.vector_array[i];
	}
	return os;
}
std::istream& operator>>(std::istream& is, vector& vector_in) {
	std::cout << "please enter your cartesian vector as x comp y_comp zcomp seperated by a space: " << std::endl;
	for (int i{}; i < vector_in.vector_length; i++) {
		is >> vector_in.vector_array[i];
	}
	return is;
}
//copy and move constructors and operators
vector::vector(vector& copy_vector)
{
	std::cout << "copy constructor called" << std::endl;
	for (size_t i{}; i < copy_vector.vector_length; i++) {
		vector_array[i] = copy_vector.vector_array[i];
	}
}
vector::vector(vector&& move_vector) noexcept
{
	std::cout << "move constructor called" << std::endl;
	for (size_t i{}; i < move_vector.vector_length; i++) {
		vector_array[i] = move_vector.vector_array[i];
	}
	for (int i{}; i < move_vector.vector_length; i++) {
		move_vector.vector_array[i] = 0;
	}
}
vector& vector::operator=(vector& copyvector)
{
	std::cout << "copy assignment operator called \n";
	if (&copyvector == this) return *this;
	for (size_t i{}; i < copyvector.vector_length; i++) {
		vector_array[i] = 0;
	}
	for (size_t i{}; i < copyvector.vector_length; i++) {
		vector_array[i] = copyvector.vector_array[i];
	}
	return *this;
}
vector& vector::operator=(vector&& movevector) noexcept
{
	std::cout << "move aasingment operator called" << std::endl;
	for (size_t i{}; i < movevector.vector_length; i++) {
		std::swap(vector_array[i], movevector.vector_array[i]);
	}
	return *this;
}
//overloaded element [] operator implementation
double& vector::operator[](size_t i) const
{
	if (i < 0 || i >= vector_length) {
		std::cout << "Error: trying to access array element out of bounds" << std::endl;
		throw("Out of Bounds Error");
	}
	return vector_array[i];
}
//dot product
double vector::dot_product(vector& dot_vector) {
	double dot_product{};
	for (int i{}; i < dot_vector.vector_length; i++) {
		dot_product += vector_array[i] * dot_vector.vector_array[i];
	}	
	return dot_product;
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
	vector one {3};
	one[0] = 1; one[1] = 3; one[2] = -2;
	std::cout << "parameterised vector: " << one;
	vector dot;
	std::cin >> dot;
	std::cout << dot;
	std::cout << "dot product of vectors one and dot: " << one.dot_product(dot) << std::endl;
	return 0;
}