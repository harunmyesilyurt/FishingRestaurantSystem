#include <iostream>
#include <fstream>
#include <locale.h>
#include <iomanip>
#include <string>

using namespace std;

//Zaman yapısı
struct Date
{
	int day, month, year;
};
// Ürün Sınıfı
class ProductClass
{
public:
	string pCode;
	string pName;
	float stockQua;
	float minStockQua;
	float Calorie;
	float Price;
	ProductClass() : pCode(""), pName(""), stockQua(0.0f), minStockQua(0.0), Calorie(0.0f), Price(0.0f)
	{
	}
	ProductClass(string uk, string ua, float sm, float msm, float k, float f) : pCode(uk), pName(ua), stockQua(sm), minStockQua(msm), Calorie(k), Price(f)
	{
	}
	//Verileri yazıp okuduğum fonksiyonlar
	void Write()
	{
		cout << "\n      ---- Product Information ---- " << endl;
		cout << "\t Product ID       :" << pCode << endl;
		cout << "\t Product Name         :" << pName << endl;
		cout << "\t Stock Amount     :" << stockQua << endl;
		cout << "\t Stock Minimum Amount :" << minStockQua << endl;
		cout << "\t Calories           :" << Calorie << endl;
		cout << "\t Price           :" << Price << endl;
	}
	void Read()
	{
		cout << "\n      ---- Product Information ---- " << endl;
		cout << "\t Product ID        :";
		cin >> pCode;
		cout << "\t Product Name         :";
		cin >> pName;
		cout << "\t Stock Amount     :";
		cin >> stockQua;
		cout << "\t Stock Minimum Amount :";
		cin >> minStockQua;
		cout << "\t Calories           :";
		cin >> Calorie;
		cout << "\t Price           :";
		cin >> Price;
	}
	~ProductClass() // Yıkan fonksiyon
	{
	}
};

class FoodClass //Yemek sınıfı
{
public:
	string fCode;
	string fName;
	float Price;
	//Verileri yazıp okuduğum fonksiyonlar
	void Write()
	{
		cout << "\n ---- Food Information ---- " << endl;
		cout << "  Product ID   :" << fCode << endl;
		cout << "  Product Name    :" << fName << endl;
		cout << "  Price       :" << Price << endl;
	}
	void Read()
	{
		cout << "\n ---- Food Information ---- " << endl;
		cout << "\t Food ID  :";
		cin >> fCode;
		cout << "\t Food Name  :";
		cin >> fName;
		cout << "\t Price       :";
		cin >> Price;
	}
};
//Global Fonksiyonlar
void Warehouse();
void Food();
void FoodSell();
void NewMaterials(string); // yemek malzemeleri ekleme
void NMaterialWrite(string);
int ProductControl(string);

//Depo fonksiyonu
void Warehouse()
{
	int Options;//Depo menüsü
	do
	{

		do
		{
			system("CLS");
			cout << "\n ---- Stock Menu ---- " << endl;
			cout << "\t 1- Kayıt ekle   " << endl;
			cout << "\t 2- Kayıt sil         " << endl;
			cout << "\t 3- Kayıt güncelle    " << endl;
			cout << "\t 4- Rapor alma          " << endl;
			cout << " \t 5- Ana menüye dönmek için     " << endl;
			cout << "\t Tercihiniz ?     :";
			cin >> Options;

		} while (!(Options >= 1 && Options < 6));
		if (Options == 1)//depoya kayıt ekleme
		{
			char Control;
			ProductClass p;
			fstream Stocks;
			Stocks.open("Warehouse.txt", ios::app);
			do
			{
				p.Read();
				Stocks << p.pCode << " " << p.pName << " " << p.stockQua << " " << p.minStockQua << " " << p.Calorie << " " << p.Price << "\n";
				cout << "Yeni kayıt eklemek istiyor musunuz ?  (y/n) ";
				cin >> Control;
			} while (!(Control == 'n'));
			Stocks.close();
		}
		if (Options == 2)//Depodan kayıt silme
		{
			int ProductID;
			ofstream TempStorage;
			ifstream Stock;
			string StockNum;
			Stock.open("Warehouse.txt");
			while (!Stock.eof())
			{
				getline(Stock, StockNum);
				cout << StockNum << endl;
			}
			Stock.close();
			cout << "Lütfen silmek istediğiniz depo ürünü için ID giriniz : ";
			cin >> ProductID;
			Stock.open("Warehouse.txt");
			TempStorage.open("TemporaryWarehouse.txt", ios::app);
			while (getline(Stock, StockNum))
			{
				string id = StockNum.substr(0, StockNum.find(" "));

				string ProductIdString = to_string(ProductID);

				if (id != ProductIdString)
				{
					TempStorage << StockNum << "\n";
				}
			}
			Stock.close();
			TempStorage.close();
			remove("Warehouse.txt");
			rename("TemporaryWarehouse.txt", "Warehouse.txt");
		}
		if (Options == 3)//Depodan kayıt güncelle
		{
			ProductClass p;
			ofstream TempStorage;
			ifstream Stock;
			string StockNum;
			int urunId;
			Stock.open("Warehouse.txt");
			while (!Stock.eof())
			{
				getline(Stock, StockNum);
				cout << StockNum << endl;
			}
			Stock.close();
			cout << "Lütfen güncellemek istediğiniz depo ürünü için ID giriniz : ";
			cin >> urunId;
			Stock.open("Warehouse.txt");
			TempStorage.open("TemporaryWarehouse.txt", ios::app);
			while (getline(Stock, StockNum))
			{

				string id = StockNum.substr(0, StockNum.find(" "));
				;
				string urunIdString = to_string(urunId);

				if (id != urunIdString)
				{
					TempStorage << StockNum << "\n";
				}
			}
			Stock.close();
			remove("Warehouse.txt");
			p.Read();
			TempStorage << p.pCode << " " << p.pName << " " << p.stockQua << " " << p.minStockQua << " " << p.Calorie << " " << p.Price << "\n";
			TempStorage.close();
			rename("TemporaryWarehouse.txt", "Warehouse.txt");
		}
		if (Options == 4)//Depodan rapor alma
		{
			ProductClass p;
			fstream Stocks;
			Stocks.open("Warehouse.txt", ios::in);

			while (Stocks >> p.pCode >> p.pName >> p.stockQua >> p.minStockQua >> p.Calorie >> p.Price)
			{
				p.Write();
				system("pause");
			}
			Stocks.close();
			cout << "Depo Listesi Bitti. " << endl;
			system("pause");
		}

	} while (Options != 5);//Ana menüye dönme 
}

void Food()//Yemek fonksiyonu
{
	int Options;
	do
	{

		do
		{
			system("CLS");
			cout << "\n  Food Menu ><(((°>  " << endl;
			cout << "\t 1- Kayıt ekle " << endl;
			cout << "\t 2- Kayıt sil         " << endl;
			cout << "\t 3- Kayıt güncelle    " << endl;
			cout << "\t 4- Rapor alma          " << endl;
			cout << " \t 5- Ana menüye dönmek için     " << endl;
			cout << "\t Tercihiniz ?     :";
			cin >> Options;

		} while (!(Options >= 1 && Options < 6));//Yemek menüsüne kayıt ekleme  
		if (Options == 1)
		{
			char Control;
			ProductClass p;
			FoodClass f;
			fstream fFood;
			fFood.open("FoodOfKind.txt", ios::app);
			do
			{
				f.Read();
				fFood << f.fCode << " " << f.fName << " " << f.Price << "\n";
				NewMaterials(f.fCode);
				cout << "Yeni kayıt eklenemek ister misiniz ?  (y/n) ";
				cin >> Control;
			} while (!(Control == 'n'));
			fFood.close();
		}

		if (Options == 2)//Yemek menüsünden kayıt silme
		{
			int FoodID;
			ofstream TempFood;
			ifstream fFood;
			string FoodNum;

			ifstream fMaterial;
			ofstream TempMaterial;
			string MaterialNum;

			fFood.open("FoodOfKind.txt");
			while (!fFood.eof())
			{
				getline(fFood, FoodNum);
				cout << FoodNum << endl;
			}
			fFood.close();
			cout << "Lütfen silmek istediğiniz depo ürünü için ID giriniz : ";
			cin >> FoodID;
			fFood.open("FoodOfKind.txt");
			TempFood.open("CasualFood.txt", ios::app);
			while (getline(fFood, FoodNum))
			{

				string ID = FoodNum.substr(0, FoodNum.find(" "));
				;
				string ProductIDString = to_string(FoodID);

				if (ID != ProductIDString)
				{
					TempFood << FoodNum << "\n";
				}
			}
			fFood.close();
			TempFood.close();
			remove("FoodOfKind.txt");
			rename("CasualFood.txt", "FoodOfKind.txt");

			fMaterial.open("Material.txt");
			TempMaterial.open("TemporaryMaterial.txt", ios::app);

			while (!fMaterial.eof())
			{
				getline(fMaterial, MaterialNum);
				string MaterialID = MaterialNum.substr(0, MaterialNum.find(" "));
				;
				string FoodIDString = to_string(FoodID);
				if (MaterialID != FoodIDString)
				{
					TempMaterial << MaterialNum << "\n";
				}
			}

			fMaterial.close();
			TempMaterial.close();
			remove("Material.txt");
			rename("TemporaryMaterial.txt", "Material.txt");
		}
		if (Options == 3)//Yemek menüsünü güncelleme
		{
			FoodClass f;
			ofstream TempFood;
			ifstream fFood;
			string FoodNum;
			ifstream fMaterial;
			ofstream TempMaterial;
			string MaterialNum;
			int ProductID;
			int Options;
			fFood.open("FoodOfKind.txt");
			while (!fFood.eof())
			{
				getline(fFood, FoodNum);
				cout << FoodNum << endl;
			}
			fFood.close();

			cout << "1- Yemeğin fiyatı ve ismini güncellemek istiyorum. " << endl
				<< endl;
			cout << "2- Yemeğin malzemelerini güncellemek istiyorum. " << endl;
			cin >> Options;
			cout << endl
				<< endl;

			cout << "Lütfen güncellemek istediğiniz yemek çeşidinin ID giriniz : ";
			cin >> ProductID;
			string fCode = to_string(ProductID);
			if (Options == 1)
			{
				fFood.open("FoodOfKind.txt");
				TempFood.open("CasualFood.txt", ios::app);
				while (getline(fFood, FoodNum))
				{

					string ID = FoodNum.substr(0, FoodNum.find(" "));

					if (ID != fCode)
					{
						TempFood << FoodNum << "\n";
					}
				}
				fFood.close();
				remove("FoodOfKind.txt");
				f.Read();
				TempFood << f.fCode << " " << f.fName << " " << f.Price << "\n";
				TempFood.close();
				rename("CasualFood.txt", "FoodOfKind.txt");
			}
			if (Options == 2)
			{
				fMaterial.open("Material.txt");
				TempMaterial.open("TemporaryMaterial.txt", ios::app);

				while (!fMaterial.eof())
				{
					getline(fMaterial, MaterialNum);
					string MaterialID = MaterialNum.substr(0, MaterialNum.find(" "));
					;
					string yemekIdString = to_string(ProductID);
					if (MaterialID != yemekIdString)
					{
						TempMaterial << MaterialNum << "\n";
					}
				}
				string ykod = to_string(ProductID);
				fMaterial.close();
				TempMaterial.close();
				remove("Material.txt");
				rename("TemporaryMaterial.txt", "Material.txt");
				NewMaterials(fCode);
			}
		}
		if (Options == 4)//Yemek menüsünün raporunu alma 
		{
			char Control;
			string Code;
			cout << " Yemek ID : ";
			cin >> Code;
			FoodClass f;
			fstream fFood;
			fFood.open("FoodOfKind.txt", ios::in);
			fFood >> f.fCode >> f.fName >> f.Price; // yemek okuma
			while (!fFood.eof())
			{
				f.Write();
				NMaterialWrite(f.fCode);
				system("pause");
				fFood >> f.fCode >> f.fName >> f.Price; // yemek okuma
				cout << " Yeni kayıt eklenemek ister misiniz ?  (y/n) ";
				cin >> Control;
			}while (!(Control == 'n'));
			fFood.close();
			system("pause");
		}
	} while (Options != 5);
}
void FoodProduc()//Yemek üretim fonksiyonu
{
	FoodClass f;
	char Answer;
	int i = 0;
	int PersonNum;
	Date d;
	float Cost = 0.0;

	string Code;
	cout << "\n Pişirilecek yemekler giriliyor... " << endl;
	fstream fProduction;
	fProduction.open("NewFood.txt", ios::app);
	do
	{
		cout << "Üretilecek yemek ID : ";
		cin >> Code;
		cout << "Bu yemek kaç kişilik pişirilecek ?";
		cin >> PersonNum;
		fstream fFood;
		fFood.open("FoodOfKind.txt", ios::in);
		fFood >> f.fCode >> f.fName >> f.Price; // yemek okunuyor

		string checkLine;
		ifstream readFProduct;

		int setControl = 0;
		readFProduct.open("FoodProduction.txt");

		while (getline(readFProduct, checkLine))
		{

			string checkCode = checkLine.substr(0, checkLine.find(" "));

			if (checkCode == Code)
			{
				setControl++;
			}


		}
		readFProduct.close();


		while (!fFood.eof())
		{


			if (Code == f.fCode)
			{
				cout << "Yemek maliyeti hesaplanıyor ..." << endl;
				string fCode, mCode;
				float Amount;
				ifstream fMaterial;
				ifstream Stocks;
				ofstream TempStorage;
				ofstream writeFProduct;
				ofstream tempFProduct;
				string readCode;
				float readCost;
				int readPersonNum;
				fMaterial.open("Material.txt");
				readFProduct.open("FoodProduction.txt");
				tempFProduct.open("temp.txt", ios::app);
				writeFProduct.open("FoodProduction.txt", ios::app);
				readFProduct >> readCode >> readCost >> readPersonNum;//yemek üretimi okuma

				int isAdded = 0;

				do
				{
					if (setControl != 0)
					{
						if (readCode != Code)
						{
							cout << " " << endl;

							tempFProduct << readCode << " " << readCost << " " << readPersonNum << "\n";// yemek üretimi yazma
						}
						else
						{
							cout << " " << endl;

							tempFProduct << readCode << " " << readCost + Cost << " " << readPersonNum + PersonNum << "\n";// yemek üretimi yazma

						}
					}
					else if (setControl == 0)
					{
						if (isAdded == 0)
						{
							isAdded++;

							cout << " " << endl;
							writeFProduct << Code << " " << Cost << " " << PersonNum << "\n";
						}


					}
					readFProduct >> readCode >> readCost >> readPersonNum;// yemek üretimi okuma

				} while (!readFProduct.eof());


				while (fMaterial >> fCode >> mCode >> Amount)
				{

					if (Code == fCode)
					{
						ProductClass p;
						Stocks.open("Warehouse.txt");
						TempStorage.open("TemporaryWarehouse.txt");
						while (Stocks >> p.pCode >> p.pName >> p.stockQua >> p.minStockQua >> p.Calorie >> p.Price)
						{
							if (p.pCode == mCode)
							{

								float Spend = PersonNum * Amount;
								//Depo yazma 
								if (p.stockQua - Spend >= p.minStockQua)
								{
									TempStorage << p.pCode << " " << p.pName << " " << p.stockQua - Spend << " " << p.minStockQua << " " << p.Calorie << " " << p.Price << "\n";
								}
								else
								{
									TempStorage << p.pCode << " " << p.pName << " " << p.stockQua << " " << p.minStockQua << " " << p.Calorie << " " << p.Price << "\n";

									if (p.stockQua - Spend > 0)//Stockta olan ve ihtiyaç duyulan malzeme ayarlama
									{
										float NeedTake = p.stockQua - Spend;
										Cost += p.Price * NeedTake;
									}
									else
									{
										Cost += p.Price * PersonNum * Amount;
									}
								}
							}

							else
							{
								TempStorage << p.pCode << " " << p.pName << " " << p.stockQua << " " << p.minStockQua << " " << p.Calorie << " " << p.Price << "\n";
							}







						}
						TempStorage.close();
						Stocks.close();
						remove("Warehouse.txt");
						rename("TemporaryWarehouse.txt", "Warehouse.txt");
					}
				}

				writeFProduct.close();
				readFProduct.close();
				tempFProduct.close();
				fMaterial.close();
				if (setControl != 0)
				{
					remove("FoodProduction.txt");
					rename("temp.txt", "FoodProduction.txt");

				}

			}
			fFood >> f.fCode >> f.fName >> f.Price;

		}
		fFood.close();

		cout << "Yeni yemek eklemek ister misiniz? (y/n)";
		cin >> Answer;
	} while (!Answer == 'n');
	fProduction.close();
}
void NMaterialWrite(string Code)//Yeni yemek malzemesi fonksiyonu
{
	int Control = 0;
	string fCode;
	string mCode;
	float Weight;
	cout << "\n Yemek malzemeleri listeleniyor..." << endl;
	fstream fMaterial;
	fMaterial.open("NewMaterial.txt", ios::in);
	cout << setw(15) << "  Malzeme kodu : " << setw(15) << " Malzeme miktarı : " << endl;
	cout << " -----------------------------------" << endl;
	fMaterial >> fCode >> mCode >> Weight;
	while (!fMaterial.eof())
	{
		if (Code == fCode)
		{
			cout << setw(15) << mCode << setw(15) << Weight << endl;
		}
		fMaterial >> fCode >> mCode >> Weight;
	}
	fMaterial.close();
}
int ProductControl(string mCode)//Ürün kontrol fonksiyonu   
{
	int Control = 0;
	ProductClass p;
	fstream Stocks;
	Stocks.open("Warehouse.txt", ios::in);
	Stocks >> p.pCode >> p.pName >> p.stockQua >> p.minStockQua >> p.Calorie >> p.Price;//Depo okuma
	while (!Stocks.eof())
	{
		if (mCode == p.pCode)
		{
			p.Write();
			Control++;
		}
		Stocks >> p.pCode >> p.pName >> p.stockQua >> p.minStockQua >> p.Calorie >> p.Price;//Depo okuma
	}
	if (Control == 0)
		cout << "Ürün stokta kayıtlı değil." << endl;
	Stocks.close();
	return Control;
}
void NewMaterials(string yCode)//Yeni malzeme fonksiyonu
{
	char Control;
	int k = 0;
	string mCode;
	float Weight;
	cout << "\n Yemek malzemeleri giriliyor..." << endl;
	fstream fMaterial;
	fMaterial.open("Material.txt", ios::app);
	do
	{
		cout << " Malzeme kodu ? ";
		cin >> mCode;
		k = ProductControl(mCode);
		if (k == 1)
		{
			cout << " Malzeme miktarı ?    ";
			cin >> Weight;
			fMaterial << yCode << " " << mCode << " " << Weight << "\n";
		}
		cout << "Yeni malzeme eklemek ister misiniz ?  (y/n) ";
		cin >> Control;
	} while (!(Control == 'n'));
	fMaterial.close();
}

void IncomeStatement()//GElir gider hesabı yapma fonksiyonu
{
	FoodClass f;
	int year, month, day;
	Date d, dReport;
	ifstream fProduct;
	string code;
	float cost;
	float spendMoney = 0.0;
	int person;
	float sell = 0;
	ifstream fFood;
	ofstream fReport;

	cout << "Lütfen hesaplamak istediğiniz tarihi giriniz : ( Day / Month / Year )";
	cin >> d.day >> d.month >> d.year;

	fProduct.open("FoodSell.txt");
	while (fProduct >> code >> day >> month >> year >> person >> cost)
	{
		if (d.day == day && d.month == month && d.year == year)
		{
			spendMoney += cost;
			fFood.open("FoodOfKind.txt");
			dReport.year = year;
			dReport.month = month;
			dReport.day = day;
			while (fFood >> f.fCode >> f.fName >> f.Price)
			{
				if (f.fCode == code)
				{
					sell += f.Price + person;
				}
			}
		}
	}
	fProduct.close();

	fReport.open("MoneyReport.txt", ios::app);

	fReport << dReport.day << " " << dReport.month << " " << dReport.year << " " << sell - spendMoney << "\n";

	fReport.close();

	cout << "Kazanç Raporunuz Oluşturuldu. " << endl;
	cout << "Kazancınız : " << sell - spendMoney << endl;

	system("pause");
}

int uretilmisurunkontrol(string Code)//Üretilen ürünlerin kontrolünün yapıldığı fonksiyon
{
	int Control = 0;
	string fCode;
	float fCost;
	int fCount;
	fstream fProduct;
	fProduct.open("FoodProduction.txt", ios::in);

	fProduct >> fCode >> fCost >> fCount;// ürün okuma
	while (!fProduct.eof())
	{
		if (Code == fCode)
		{


			if (fCount > 0)
			{
				cout << "Ürün ID : " << fCode << "\n Ürün Maliyeti : " << fCost << "\n Elde bulunan ürün miktarı : " << fCount << "\n";//Ürün yazma
				Control++;
			}
			else
			{
				cout << "Ürün ID : " << fCode << "\n Ürün Maliyeti : " << fCost << "\n Elde bulunan ürün miktarı : " << fCount << "\n Ürün Stokta Mevcut Değil...";
			}
		}
		fProduct >> fCode >> fCost >> fCount;// ürün okuma
	}
	fProduct.close();
	return Control;
}

void YeniSatıs()
{
	char Control;
	int k = 0;
	string mCode;
	float Weight;
	string fCode;
	int fCount;
	float fCost;
	Date d;
	cout << "\n Satılacak yemek bilgileri giriliyor... " << endl;
	fstream fFoodSell;
	fstream fFProduct;
	fstream fTempProduct;
	fFoodSell.open("FoodSell.txt", ios::app);
	do
	{
		cout << " Yemek ID ? ";
		cin >> mCode;
		k = uretilmisurunkontrol(mCode);
		if (k == 1)
		{
			fFProduct.open("FoodProduction.txt", ios::in);
			cout << " miktar    ?    ";
			cin >> Weight;

			fTempProduct.open("TempProduction.txt", ios::app);
			while (fFProduct >> fCode >> fCost >> fCount)
			{
				if (fCode == mCode)
				{


					if (fCount >= Weight)
					{
						cout << "Tarih giriniz (Gün/ay/yıl) : " << endl;
						cin >> d.day >> d.month >> d.year;

						fFoodSell << mCode << " " << d.day << " " << d.month << " " << d.year << " " << fCount << " " << fCost << "\n";
						fTempProduct << fCode << " " << fCost << " " << fCount - Weight << "\n";
					}
					else
					{
						cout << Weight - fCount << "Adet ürün stokta eksiktir." << endl;
						fTempProduct << fCode << " " << fCost << " " << fCount << "\n";
					}
				}
				else
				{
					fTempProduct << fCode << " " << fCost << " " << fCount << "\n";
				}
			}
			fTempProduct.close();
			fFProduct.close();
			remove("FoodProduction.txt");
			rename("TempProduction.txt", "FoodProduction.txt");
		}
		else
		{
			cout << "ID numarası " << mCode << "olan yemek daha üretilmedi..." << endl;

		}
		cout << " Yeni malzeme eklenecek mi ?  (y/n) ";
		cin >> Control;
	} while (!(Control == 'n'));
	fFoodSell.close();
}
int main()//ANA işlemlerin olduğu fonksiyon
{
	setlocale(LC_ALL, "Turkish");
	int Options;//Ana menü 

	do
	{
		do
		{
			system("CLS");

			cout << "\n ><(((°>     FishingHouse      <°(((><" << endl;
			cout << "\t 1- Depo işlemleri (Warehouse operations)   " << endl;
			cout << "\t 2- Yemek işlemleri (Food operations)   " << endl;
			cout << "\t 3- Yemek üretim (Food Production)   " << endl;
			cout << "\t 4- Yemek satış  (Food Sell)   " << endl;
			cout << "\t 5- Gelir gider hesaplama     " << endl;
			cout << "\t 6- Exit    " << endl;
			cout << "\t Tercihiniz ?     :";

			cin >> Options;

		} while (!(Options >= 1 && Options < 7));//İlişkili fonksiyonları bağlama 
		if (Options == 1)
			Warehouse();
		if (Options == 2)
			Food();
		if (Options == 3)
			FoodProduc();
		if (Options == 4)
			YeniSatıs();
		if (Options == 5)
			IncomeStatement();
	} while (Options != 6);

}
