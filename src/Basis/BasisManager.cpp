#include <BasisManager.h>

BasisManager* BasisManager::instance = 0;
BasisManager* BasisManager::getInstance()
{
	if (!instance) {
		instance = new BasisManager();
		return instance;
	}
	else {
		return instance;
	}
};

void BasisManager::selectBase(Base b) {
	// TODO: add controls here, such as: b must be an element of basis vector
	this->selected = b;
}

void BasisManager::addBase(Base b) {
	this-> bases.push_back(b);

	// If it's there's just this one in the vector, then it's automatically selected
		if (this->bases.size() == 1)
		this->selectBase(b);
}

std::vector<Base> BasisManager::getBasisList() {
	return this->bases;
}

std::vector<Base> BasisManager::getBasisList(Source s) {
	switch (s) {
		case MEMORY:
			return this->bases;
			break;

		case FILE:
			//TODO: read from default basis file
			break;
	}
	return this->bases;
}


// --- Factory Methods --- //
void BasisManager::build1DCartesian(double mesh, unsigned int nbox){
	BasisManager::Builder b;
	Base base = b.addContinuous(mesh, nbox).build(Base::basePreset::Cartesian, 1);

	return;
}


void BasisManager::build1DCartesian(double start, double end, double mesh) {
	BasisManager::Builder b;
	Base base = b.addContinuous(start, end, mesh).build(Base::basePreset::Cartesian, 1);

	return;
}


void BasisManager::build1DCartesian(double start, double end, unsigned int nbox){
	BasisManager::Builder b;
	Base base = b.addContinuous(start, end, nbox).build(Base::basePreset::Cartesian, 1);

	return;
}


// --- End Factory --- //
Base BasisManager::Builder::build() {
	//TODO: Eventually add controls...
    int dimension = 0;

	return Base(Base::basePreset::Custom, dimension, c_base, d_base);
}

Base BasisManager::Builder::build(Base::basePreset b, int dimension) {
    //TODO: Eventually add controls...
        return Base(b, dimension, c_base, d_base);
    }

Base BasisManager::Builder::build(Base::basePreset b, int dimension, double mesh, int nbox) {
    //TODO: Eventually add controls...

    switch(b){

        case Base::basePreset::Custom: throw std::invalid_argument("Custom basis not meaningful with parameters!");
            break;
        case Base::basePreset::Cartesian:
            std::cout<< "Building Cartesian basis in " << dimension << "dimensions, with nbox = " << nbox << ", mesh = " << mesh << std::endl;
            for(int i = 0; i < dimension; i++)
            {
                this->addContinuous(mesh, nbox);
            }
            break;
        case Base::basePreset::Cylindrical: std::invalid_argument("Not implemented");
            break;
        case Base::basePreset::Spherical: std::invalid_argument("Not implemented");
            break;
        default: throw std::invalid_argument("Wrong basis type or initialization meaningless!");
            break;

    }

    return Base(b, dimension, c_base, d_base);
}


BasisManager::Builder BasisManager::Builder::addDiscrete(int start, int end, int step) {
	//TODO: Eventually add controls...
	d_base.push_back(DiscreteBase(start, end, step));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuous(double mesh, unsigned int nbox) {
	//TODO: Eventually add controls...
	c_base.push_back(ContinuousBase(mesh, nbox));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuous(double start, double end, double mesh) {
	//TODO: Eventually add controls...
	c_base.push_back(ContinuousBase(start, end, mesh));
	return *this;
}
BasisManager::Builder BasisManager::Builder::addContinuous(double start, double end, unsigned int nbox) {
	//TODO: Eventually add controls...
	c_base.push_back(ContinuousBase(start, end, nbox));
	return *this;
}
