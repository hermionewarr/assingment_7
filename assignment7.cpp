//assignment 7
//Hermione Warr
//16/03/2020

#include<iostream>

class vector 
{
	friend std::ostream& operator<<(std::ostream& os, const vector& out_vector);
	friend std::istream& operator>>(std::istream& is, vector& vector_in);

protected:
	double* vector_array{ nullptr };
	double vector_length{};
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
	double component(int component) {return vector_array[component];}
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
		if (out_vector.vector_array[i] > 0 && i>0) {
			os << "+";
		}
		os << out_vector.vector_array[i] << "e" << i + 1;
	}
	return os;
}
std::istream& operator>>(std::istream& is, vector& vector_in) {
	std::cout << "please enter your cartesian vector as its components seperated by a space: " << std::endl;
	for (size_t i{}; i < vector_in.vector_length; i++) {
		is >> vector_in.vector_array[i];
	}
	return is;
}
//copy and move constructors and operators
vector::vector(vector& copy_vector)
{
	std::cout << "copy constructor called" << std::endl;
	vector_array = nullptr;
	vector_length = copy_vector.vector_length;
	vector_array = new double[vector_length];
	for (size_t i{}; i < copy_vector.vector_length; i++) {
		vector_array[i] = copy_vector[i];
	}
}
vector::vector(vector&& move_vector) noexcept
{
	std::cout << "move constructor called" << std::endl;
	vector_length = move_vector.vector_length;
	vector_array = move_vector.vector_array;
	move_vector.vector_length = 0;
	move_vector.vector_array = nullptr;
	
}
vector& vector::operator=(vector& copyvector)
{
	std::cout << "copy assignment operator called \n";
	if (&copyvector == this) { return *this;}
	//delete this objects array first
	delete[] vector_array;
	vector_array = nullptr;
	vector_length = 0;
	//copy into new array
	vector_length = copyvector.vector_length;
	vector_array = new double[vector_length];
	for (size_t i{}; i < copyvector.vector_length; i++) {
		vector_array[i] = copyvector[i];
	}
	return *this;
}
vector& vector::operator=(vector&& movevector) noexcept
{
	std::cout << "move aasingment operator called" << std::endl;
	std::swap(vector_length, movevector.vector_length);
	std::swap(vector_array, movevector.vector_array);
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
	if (vector_length == dot_vector.vector_length) {
		for (int i{}; i < dot_vector.vector_length; i++) {
			dot_product += vector_array[i] * dot_vector.vector_array[i];
		}
	}
	else { std::cout << "Your vectors are not the same the length!\n"; }
	return dot_product;
}

class four_vector :public vector
{
	friend std::ostream& operator<<(std::ostream& os, const four_vector& out_4_vector);
protected:
	//vector four{ 4 };
public:
	four_vector() : vector{ 4 } {};
	four_vector(double ct, double x_comp, double y_comp, double z_comp) : vector{ 4 }
	{
		vector_array[0] = ct, vector_array[1] = x_comp, vector_array[2] = y_comp, vector_array[3] = z_comp;
	}
	four_vector(const double ct, vector three_vector) : vector{ 4 }
	{
		vector_array[0] = ct;
		for (int i{}; i < 3; i++) {
			vector_array[i + 1] = three_vector[i];
		}
	}
	~four_vector() { std::cout << "destroying 4-vector\n"; }
	//move and copy constructors and assingment operators
	four_vector(four_vector&);
	four_vector(four_vector&&) noexcept;
	four_vector& operator=(four_vector&);
	four_vector& operator=(four_vector&&) noexcept;
	//acessing components 
	double component(int component) { return vector_array[component]; }
	double length() const { return vector_length; }
	//dot
	double dot_product(four_vector& dottie_boi);
};
/*---------------------------
member functions of 4-vector
----------------------------*/
//overload friend operators for output and input stream
std::ostream& operator<<(std::ostream& os, const four_vector& out_4_vector)
{
	os << "{";
	for (int i{}; i < 4; i++) {
		os << out_4_vector.vector_array[i] << "e" << i + 1;
		if (i < 3) {os << ", ";}
	}
	os << "}";
	return os;
}
//copy and move constructors and operators
four_vector::four_vector(four_vector& copyvector)
{
	std::cout << "copy constructor called" << std::endl;
	vector_array = nullptr;
	vector_length = 4;
	if (vector_length > 0) {
		vector_array = new double[vector_length];
		for (size_t i{}; i < 4; i++) {
			vector_array[i] = copyvector[i];
		}
	}
}
four_vector::four_vector(four_vector&& move_vector) noexcept
{
	std::cout << "move constructor called" << std::endl;
	vector_length = move_vector.vector_length;
	vector_array = move_vector.vector_array;
	move_vector.vector_length = 0;
	move_vector.vector_array = nullptr;
}
four_vector& four_vector::operator=(four_vector& copyvector)
{
	std::cout << "copy assignment operator called \n";
	if (&copyvector == this) { return *this; }
	//delete this objects array first
	delete[] vector_array;
	vector_array = nullptr;
	vector_length = 0;
	//copy into new array
	vector_length = copyvector.vector_length;
	vector_array = new double[vector_length];
	for (size_t i{}; i < copyvector.vector_length; i++) {
		vector_array[i] = copyvector[i];
	}
	return *this;
}
four_vector& four_vector::operator=(four_vector&& movevector) noexcept
{
	std::cout << "move aasingment operator called" << std::endl;
	std::swap(vector_length, movevector.vector_length);
	std::swap(vector_array, movevector.vector_array);
	return *this;
}
//dot product
double four_vector::dot_product(four_vector& dot_vector) {
	double dot_product{};
	if (vector_length == dot_vector.vector_length) {
		for (int i{}; i < dot_vector.vector_length; i++) {
			dot_product += vector_array[i] * dot_vector.vector_array[i];
		}
	}
	else { std::cout << "Your vectors are not the same the length!\n"; }
	return dot_product;
}

class particle
{
private:
public:
};

int main() {
	vector default_example;
	std::cout << "default constructor:" << default_example<< std::endl;
	vector one {3};
	one[0] = 1; one[1] = 3; one[2] = -2;
	std::cout << "parameterised vector: " << one << std::endl;
	std::cout << "second component of vector one: " << one.component(2) << std::endl;
	size_t dimensions{};
	std::cout << "please enter the number of dimensions of your vector: ";
	std::cin >> dimensions;
	vector dot{dimensions};
	std::cin >> dot;
	std::cout << "dot vector: " << dot << std::endl;
	std::cout << "dot product of vectors one and dot: " << one.dot_product(dot) << std::endl;
	//4-vector
	four_vector doubles{10,2,3,4};
	four_vector double_vector{12,one};
	std::cout << "4-vector doubles: " << doubles << std::endl;
	std::cout << "4-vector double_vector: " << double_vector << std::endl;
	return 0;
}