//Assignment 7 -  Inherited classes
//Hermione Warr
//16/03/2020

#include<iostream>

//vector class
class vector 
{
	friend std::ostream& operator<<(std::ostream& os, const vector& out_vector);
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
/*----------------------------
  member functions of vector
-----------------------------*/
//overload friend operators for output stream
std::ostream& operator<<(std::ostream& os, const vector &out_vector)
{
	os << "{";
	for (int i{}; i < out_vector.vector_length; i++) {
		os << out_vector.vector_array[i];
		if (i != out_vector.vector_length-1) { os << ", "; }
	}
	os << "}";
	return os;
}
//copy and move constructors and operators
vector::vector(vector& copy_vector)
{
	std::cout << "copy constructor called" << std::endl;
	vector_array = nullptr;
	vector_length = copy_vector.vector_length;
	if (vector_length > 0) {
		vector_array = new double[vector_length];
		for (size_t i{}; i < copy_vector.vector_length; i++) {
			vector_array[i] = copy_vector[i];
		}
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
	if (vector_length > 0) {
		vector_array = new double[vector_length];
		for (size_t i{}; i < copyvector.vector_length; i++) {
			vector_array[i] = copyvector[i];
		}
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
double vector::dot_product(vector& dot_vector) 
{
	double dot_product{};
	if (vector_length == dot_vector.vector_length) {
		for (int i{}; i < dot_vector.vector_length; i++) {
			dot_product += vector_array[i] * dot_vector.vector_array[i];
		}
	}
	else { std::cout << "Your vectors are not the same the length!\n"; }
	return dot_product;
}
//4-vector class derived from vector class
class four_vector :public vector
{
	friend std::ostream& operator<<(std::ostream& os, const four_vector& out_4_vector);
public:
	four_vector() : vector{ 4 } {};
	four_vector(double x_comp, double y_comp, double z_comp, double ct) : vector{ 4 }
	{
		vector_array[0] = x_comp, vector_array[1] = y_comp, vector_array[2] = z_comp, vector_array[3] = ct;
	}
	four_vector(vector three_vector, const double ct) : vector{ 4 }
	{
		vector_array[3] = ct;
		for (int i{}; i < 3; i++) {
			vector_array[i] = three_vector[i];
		}
	}
	~four_vector() { std::cout << "destroying 4-vector\n"; }
	//move and copy constructors and assingment operators
	four_vector(four_vector&);
	four_vector(four_vector&&) noexcept;
	four_vector& operator=(four_vector&);
	four_vector& operator=(four_vector&&) noexcept;
	//acessing components 
	double x_component() { return vector_array[0]; }
	double y_component() { return vector_array[1]; }
	double z_component() { return vector_array[2]; }
	double ct_component() { return vector_array[3]; }
	double length() const { return vector_length; }
	//dot
	double dot_product(four_vector& dottie_boi);
	//lorentz boost
	four_vector lorentz_boost(vector beta);
};
/*---------------------------
member functions of 4-vector
----------------------------*/
//overload friend operators for output and input stream
std::ostream& operator<<(std::ostream& os, const four_vector& out_4_vector)
{
	os << "{";
	for (int i{}; i < 4; i++) {
		os << out_4_vector.vector_array[i];
		if (i == 0) { os << "x"; }
		else if (i == 1) { os << "y"; }
		else if (i == 2) { os << "z"; }
		else if (i == 3) { os << "ct"; }
		if (i < 3) {os << ", ";}
	}
	os << "}";
	return os;
}
//copy and move constructors and operators
four_vector::four_vector(four_vector& copyvector)
{
	std::cout << "4 copy constructor called" << std::endl;
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
	std::cout << "4 move constructor called" << std::endl;
	vector_length = move_vector.vector_length;
	vector_array = move_vector.vector_array;
	move_vector.vector_length = 0;
	move_vector.vector_array = nullptr;
}
four_vector& four_vector::operator=(four_vector& copyvector)
{
	std::cout << "4 copy assignment operator called \n";
	if (&copyvector == this) { return *this; }
	//delete this objects array first
	delete[] vector_array;
	vector_array = nullptr;
	vector_length = 0;
	//copy into new array
	vector_length = copyvector.vector_length;
	if (vector_length > 0) {
		vector_array = new double[vector_length];
		for (size_t i{}; i < copyvector.vector_length; i++) {
			vector_array[i] = copyvector[i];
		}
	}
	return *this;
}
four_vector& four_vector::operator=(four_vector&& movevector) noexcept
{
	std::cout << "4 move aasingment operator called" << std::endl;
	std::swap(vector_length, movevector.vector_length);
	std::swap(vector_array, movevector.vector_array);
	return *this;
}
//dot product
double four_vector::dot_product(four_vector& dot_vector) {
	double dot_product{};
	dot_product = vector_array[3] * dot_vector[3];
		for (int i{}; i < 3; i++) {
			dot_product -= vector_array[i] * dot_vector.vector_array[i];
		}
	return dot_product;
}
four_vector four_vector::lorentz_boost(vector beta)
{
	double ct{}; double gamma{}; double ct_prime{}; 
	vector r{ 3 }; vector r_prime{ 3 };
	r[0] = vector_array[0]; r[1] = vector_array[1]; r[2] = vector_array[2];
	ct = vector_array[3];
	gamma = 1 / sqrt(1 - beta.dot_product(beta));
	ct_prime = gamma * (ct - beta.dot_product(r));
	for (int i{}; i < 3; i++) {
		r_prime[i] = r[i] + ((gamma - 1) * (r.dot_product(beta) / beta.dot_product(beta)) - gamma * ct) * beta[i];
	}
	four_vector lorentz_boosted_vector{ r_prime, ct_prime };
	std::cout << "beta is: " << beta << std::endl;
	std::cout << "gamma factor: " << gamma << std::endl;
	std::cout << "ct prime: " << ct_prime << std::endl;
	std::cout << "r prime: " << r_prime << std::endl;
	return lorentz_boosted_vector;
}
//particle class
class particle
{
private:
	four_vector position{};
	double mass{};
	vector beta{ 3 };
public:
	particle() : position{0,0,0,0} {}
	particle(four_vector particle_position, double m, vector B) :
		position{ particle_position }, mass{ m }, beta{B} {}
	~particle() { std::cout << "particle destructor called" << std::endl; }
	//return particle coordinates
	four_vector coordinates() { return position; }
	//return mass
	double particle_mass() { return mass; }
	//gamma
	double gamma_factor() {
		double gamma = 1 / (1 - beta.dot_product(beta));
		return gamma;
	}
	//total particle energy 
	double total_energy(){
		double energy = gamma_factor() * mass;
		return energy;
	}
	//particle momentum
	vector three_momentum() {
		vector momentum{ 3 };
		for (int i{}; i < 3; i++) {
			momentum[i] = gamma_factor() * mass * beta[i];
		}
		return momentum;
	}
};

int main() {
	/*-------------
	  Vector class
	--------------*/
	vector default_example;
	std::cout << "Default constructor:" << default_example<< std::endl;
	vector one {3};
	one[0] = 1; one[1] = 3; one[2] = -2;
	std::cout << "Parameterised vector: " << one << std::endl;
	//acessing a vector component
	std::cout << "Second component of vector one: " << one.component(1) << std::endl;
	//Deep copy using copy constructor
	vector copy_one{ one };
	std::cout << "Deep copy of vector one: " << copy_one << std::endl;
	//Deep copy by assignment
	vector copy_assignment{};
	copy_assignment = one;
	std::cout << "Copy by assignemnt of vector one: " << copy_assignment <<std::endl;
	//Move construction demonstration
	vector move_one{ std::move(one) };
	std::cout << "Moving vector one to vector move_one with the move constructor: " << move_one << std::endl;
	//Move assignment demonstration
	vector move_assignment{};
	move_assignment = std::move(copy_one);
	std::cout << "Move vector copy_one to vector move_assignemt by assignment: " << move_assignment << std::endl;
	//dot product
	vector dot{3};
	dot[0] = 1; dot[1] = 2; dot[2] = 3;
	vector two{ 3 };
	two[0] = -6; two[1] = 5; two[2] = 4;
	std::cout << "Vector dot: " << dot << std::endl;
	std::cout << "Vector two: " << two << std::endl;
	std::cout << "Dot product of vectors two and dot: " << two.dot_product(dot) << std::endl;
	/*----------------
	  4-vector class
	------------------*/
	four_vector first{10,2,3,4};
	four_vector second{two,12};
	std::cout << "4-vector first: " << first << std::endl;
	std::cout << "4-vector second: " << second << std::endl;
	//acsessing components
	std::cout << "ct component of four vector first: " << first.ct_component() << std::endl;
	//Deep copy using copy constructor
	four_vector four_vector_copy{ first };
	std::cout << "Deep copy of 4-vector first: " << four_vector_copy << std::endl;
	//Deep copy by assignment
	four_vector four_vector_copy_assignment{};
	four_vector_copy_assignment = first;
	std::cout << "Copy by assignemnt of 4-vector first: " << four_vector_copy_assignment << std::endl;
	//Move construction demonstration
	four_vector four_vector_move{ std::move(first) };
	std::cout << "Moving 4-vector first to four_vector_move with the 4-vector move constructor: " << four_vector_move << std::endl;
	//Move assignment demonstration
	four_vector four_move_assignment{};
	four_move_assignment = std::move(second);
	std::cout << "Move 4-vector second to four_move_assignemt by assignment: " << four_move_assignment << std::endl;
	//Dot product
	four_vector four_dot{ 1,-4,2,3 };
	std::cout << "Dot product: four_vector_copy dotted with four_dot: " << four_vector_copy.dot_product(four_dot) << std::endl;
	//lorentz boost
	vector beta{ 3 };
	beta[0] = 0.6; beta[1] = 0.4; beta[2] = 0.5;
	four_vector unprimed{ 2,4,6,3 };
	std::cout << "Unprimed 4-vecotr is: " << unprimed << std::endl;
	std::cout << "The lorentz boost of the unprimed 4-vector is: " << unprimed.lorentz_boost(beta) << std::endl;
	/*----------------
	  Particle class
	------------------*/
	double ct{ 0.5 };
	double electron_mass{ 0.511 };
	four_vector particle_position{ 1,2,3,ct };
	particle electron{ particle_position, electron_mass, beta };
	std::cout << "Electron coordinates: " << electron.coordinates() << std::endl;
	std::cout << "Electron mass: " << electron_mass << " MeV/c^2" << std::endl;
	std::cout << "Electron gamma factor: " << electron.gamma_factor() <<std::endl;
	std::cout << "Total energy of electron: " << electron.total_energy() << " MeV" << std::endl;
	std::cout << "Three momentum of the electron: " << electron.three_momentum() << std::endl;

	return 0;
}