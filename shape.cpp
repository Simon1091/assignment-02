#include "shape.h"
#include "constants.h"
#include <iostream>
#include <string>



Shape::Shape(const std::string & type) {
	setType(type);
}
Shape::~Shape() {

}
std::string Shape::getType() {
	return type_;
}
void Shape::setType(const std::string &type) {
	type_ = type;
	if (type_art_ == "empty")
	{
		type_art_ = "     \n"
			"     \n"
			"     \n";
	}
	else if (type_art_ == "triangle")
	{
		type_art_ = "  ,  \n"
			" / \\ \n"
			"/___\\\n";
	}
	else if (type_art_ == "square") {
		type_art_ = ".---.\n"
			"|    |\n"
			"'---'\n";
	}
}
	void Shape::drawToBuffer(Buffer & b, unsigned int x, unsigned int y) const{
		b.set(x, y, type_art_);

		
	}
	bool Shape::isHappy(const Neighborhood & n, unsigned int pos_x, unsigned int pos_y)const {
		if (n.get(pos_x, pos_y).getType() == "empty")
			return true;

		unsigned int x_min = (pos_x == 0) ? pos_x : pos_x - 1;
		unsigned int y_min = (pos_y == 0) ? pos_y : pos_y - 1;

		unsigned int x_max = (pos_x == n.size_x - 1) ? pos_x : pos_x + 1;
		unsigned int y_max = (pos_y == n.size_y - 1) ? pos_y : pos_y + 1;

		double alike = 0;
		double different = 0;

		for (unsigned int x = x_min; x <= x_max; x++) {
			for (unsigned int y = y_min; y <= y_max; y++) {
				if (x == pos_x && y == pos_y)
					continue;
				else if (n.get(x, y).getType() == "empty")
					continue;
				else if (n.get(x, y).getType() == n.get(pos_x, pos_y).getType())
					alike++;
				else
					different++;
			}
		}

		return (different || alike)
			&& (different == 0 || alike / different >= RATIO_ALIKE_HAPPY)
			&& (alike == 0 || different / alike >= RATIO_ALIKE_HAPPY);
	}


