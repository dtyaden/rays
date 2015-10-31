class Triangle : Geom {
	
	public:
		Vec3 a, b, c;
		Triangle () {};
		Triangle (Vec3 x, Vec3 y, Vec3 z) : a(x), b(y), c(z) {};
};
