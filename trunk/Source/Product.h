#pragma once
#include <BWAPI.h>

/**
 * All possible types of Product.
 */
enum ProductType
{
	NoProduct,
	BuildProduct,
	TechProduct,
	UpgradeProduct,
	ExpandProduct
};

/**
 * A Product is a unit/building, tech or upgrade that we intend to buy. Each Product has only one ProductType and only the corresponding ***type attribute filled in.
 */
class Product
{
public:
	/**
	 * The unit/building that we want.
	 */
	BWAPI::UnitType buildtype;
	
	/**
	 * The tech that we want.
	 */
	BWAPI::TechType techtype;

	/**
	 * The upgrade that we want.
	 */
	BWAPI::UpgradeType upgradetype;

	/**
	 * The type of this Product.
	 */
	ProductType type;

	/**
	 * Create a new empty Product.
	 */
	Product();

	/**
	 * Create a new Product of type BuildProduct
	 * \param t the UnitType that we want
	 * \param p the priority of this Product
	 */
	Product(BWAPI::UnitType t, int p);

	/**
	 * Create a new Product of type TechProduct
	 * \param t the TechType that we want
	 * \param p the priority of this Product
	 */
	Product(BWAPI::TechType t, int p);

	/**
	 * Create a new Product of type UpgradeProduct
	 * \param t the UpgradeType that we want
	 * \param p the priority of this Product
	 */
	Product(BWAPI::UpgradeType t, int p);

	int priority;
	int mineralPrice();
	int gasPrice();

	/**
	 * Sets the ProductType of the Product to ExpandType. To create an expand Product: Product p = Product().expand();
	 */
	Product expand();

	/**
	 * Equality comparison operator.
	 */
	bool operator==(const Product& other) const;
};