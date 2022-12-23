// Michael McCain
// 03/06/2022
// CIS 1202
// Pick List
// This program simulates a pick list for a company's warehouse operation.

// To use: 
// 1. Enter a product ID followed by a name/description and price.
// 2. After entering all the products the user will be prompted to input product IDs to pick and display.
// 3. Products will display in the order that they are entered along w/ the sum of all picked products and the avg price.


																		// Libraries
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<string>
#include <memory>
#include <vector>
#include<cstring>
#include<cstdlib>
#include<cctype>
using namespace std;
																		// Structures 
const int SZ = 51;
struct Product_S
{
	int ID;									// Product ID (5 digits)
	char cstrName[SZ];						// Product Name w/ Description
	double price;							// Product Price
};
																		// Prototypes
Product_S Create_Product(Product_S prodStruct_p [],int&, const int);
void Fetch_Product(vector<int>&);
																		// Main Program
int main()
{
	// Initializers
	int count = 0;
	const int SIZE = 100;
	vector<int> productIDs;					// Vector Stores product IDs
	unique_ptr<double> sum_p(new double);	// DMA variables
	unique_ptr<double> avg_p (new double);
	*avg_p = 0; 
	*sum_p = 0;
	Product_S* prodStruct_p = nullptr;		//  SIZE 100 ARRAY
	prodStruct_p = new Product_S[SIZE];			
	int menuSelect = 0;
	int index = 0;
	bool found = false;
	int a = 0;
	int n = 0;
	cout << setprecision(2) << fixed;

	// Start
	*prodStruct_p = Create_Product(prodStruct_p,count, SIZE);	// Create product information
	Fetch_Product(productIDs);									// fetch orders				
	cout << "\nProduct List" << endl;	
	cout << "\nOrder#" << right <<setw(12) << "Product ID" << setw(34) << "Product Name & Description" << setw(18)
		<< "Price" << endl;
	for (index = 0; index < productIDs.size(); index++)
	{
		for (a = 0; a < count; a++)
		{
			if (productIDs[index] == prodStruct_p[a].ID && a != count)
			{
				// display match
				cout << index + 1 << ". " << setw(12) << prodStruct_p[a].ID << setw(30) << prodStruct_p[a].cstrName << setw(21)
					<< "$" << prodStruct_p[a].price << endl;
				*sum_p = *sum_p + prodStruct_p[a].price;
				n++;
				break;
			}			
		}
		if (productIDs[index] != prodStruct_p[a].ID && a == count)
		{
			cout << index + 1 << ". " << setw(12) << productIDs[index] << setw(31) << " NO MATCH " << endl;
		}
	}
	*avg_p = *sum_p / n;
	cout << "\nSum of picked products: $" << *sum_p;
	cout << "\nAverage price of picked products: $" << *avg_p << "\n";

	// End Program
	cout << "\nExiting program.";
	cout << endl << endl;
	system("pause");
	return 0;
}
// Definitions																	
		
																		// Create Product
Product_S Create_Product(Product_S prodStruct_p [],int &count, const int SIZE)
{
	// The user will enter the data for a product into a structure and store the structure in the array.
	bool again = true;
	do {
		cout << "Create Product ID (MAX 5 digits) OR enter -1 to proceed> "; // Data Collection
		int input = 0;
		do 
		{
			cin >> input;
			if (!cin)		 // compare input types
			{
				cout << "\nInvalid ID. Product IDs must be digits>";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else break;
		} while (true);
		if (input == -1)
		{
			again = false;
		}
		else 
		{
			string strInput = to_string(input);		// convert input to string and use only the first 5 characters.
			strInput = strInput.substr(0,5);
			int convInput = stoi(strInput);
			prodStruct_p[count].ID = convInput;
			cout << "Enter Product Name and Brief Description> ";
			cin.ignore();
			cin.get(prodStruct_p[count].cstrName, SIZE);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter Price for " << ">";
			cin >> prodStruct_p[count].price;
			count++;
			if (count == 100)
			{
				cout << "\n Warehouse at capacity";
			}
		}
	} while (again == true);
	return *prodStruct_p;
};
																		// Fetch Product
void Fetch_Product(vector<int>& productIDs)
{
	// the user will enter the IDs of products ordered by customers and store the IDs in a vector
	bool again = true;
	do {
		cout << "\nEnter Product IDs from customer orders OR enter -1 to print order list> ";
		int orderID = 0;
		do 
		{
			cin >> orderID;
			if (!cin)		 // compare input types
			{
				cout << "\nInvalid ID. Product IDs must be digits>";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else break;
		} while (true);

		if (orderID != -1)
		{
			string strInput = to_string(orderID);		// convert input to string and use only the first 5 characters.
			strInput = strInput.substr(0, 5);
			int convInput = stoi(strInput);
			productIDs.push_back(convInput); 	// Stores ID in Vector
		}
		else if (orderID == -1)
		{
			again = false;
		}
	} while (again == true);
	cout << endl <<  productIDs.size() << " orders to process." << endl;
}