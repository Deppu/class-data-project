#include <iostream>
#include <math.h>	//untuk fungsi pow()pangkat dan sqrt()akar untuk simpangan baku di statistic_pull()
#include <fstream>	//untuk file
#include <stdlib.h>
using namespace std;

struct struct_mhs	//struct paling dalam
{
	string nama;
	long int nim;
	float nilai;
};
struct struct_kelas
{
	int banyak_mhs;
	float mean,std_dev,max,min,med,mod;	//statistik
	string max_achieve,min_achieve;	//nama peraih max min
	long int max_achieve_nim,min_achieve_nim;	//nim peraih max min
	char nama;	//nama kelas (1 karakter saja)
	struct_mhs mhs[64];	//maksimal 64 mahasiswa saja
};

struct data_utama {
	int banyak_kls=0,global_max_address,global_min_address,total_mhs=0; //max min untuk pengurutan kelas
	float global_max=0,global_min=100,global_mean;
	struct_kelas kelas[64];
}data;

void menu(); //dideklarasi di awal supaya bisa dipanggil nanti

void menu_kelas();	//sama

void menu_tampil();	//sama juga

void class_swap(struct_mhs *p,struct_mhs *q){	//pindah struct untuk pengurutan mahasiswa

	struct_mhs temp=*p;	//tunjuk ke alamat array yang mau diubah
						//terus nilainya dipindah pakai *
	*p=*q;

	*q=temp;

}

void class_score_bub_sort(int n,struct_mhs arr[]){ 	//bubble sort struct mahasiswa
													//untuk mencari median, modus, dan simpangan baku
	bool done=false;	//array belum terurut

	while(done==false){

		done=true;	//array anggap terurut agar bisa keluar while()

		for(int i=0;i<data.kelas[n].banyak_mhs-1;i++){

			if(arr[i].nilai>arr[i+1].nilai){

				done=false;	//array ternyata belum terurut; ulang lagi

				class_swap(&arr[i],&arr[i+1]);	//pindah pakai swap

			}

		}

	}

}

void name_search(string target){

	bool found=false;	//anggap belum ditemukan

	for(int i=0;i<data.banyak_kls;i++){	//perulangan kelas

		for(int j=0;j<data.kelas[i].banyak_mhs;j++){	//perulangan mahasiswa

			if(target==data.kelas[i].mhs[j].nama){	//perbandingan nama target

				cout<<"\nDITEMUKAN DI KELAS "<<data.kelas[i].nama<<"!";

				cout<<"\nNama\t: "<<data.kelas[i].mhs[j].nama<<endl;

				cout<<"NIM\t: "<<data.kelas[i].mhs[j].nim<<endl;

				cout<<"Nilai\t: "<<data.kelas[i].mhs[j].nilai<<endl<<endl;

				found=true;	//ditemukan

			}

		}

	}

	if(found==false){	//ternyata gak ketemu

		cout<<"\n"<<target<<" TIDAK DITEMUKAN!\n\n";

	}

}

void nim_search(long int target){	//sama kayak nama, tapi targetnya long int

	bool found=false;

	for(int i=0;i<data.banyak_kls;i++){

		for(int j=0;j<data.kelas[i].banyak_mhs;j++){

			if(target==data.kelas[i].mhs[j].nim){

				cout<<"\nDITEMUKAN DI KELAS "<<data.kelas[i].nama<<"!";

				cout<<"\nNama\t: "<<data.kelas[i].mhs[j].nama<<endl;

				cout<<"NIM\t: "<<data.kelas[i].mhs[j].nim<<endl;

				cout<<"Nilai\t: "<<data.kelas[i].mhs[j].nilai<<endl<<endl;

				found=true;

			}

		}

	}

	if(found==false){

		cout<<"\nNIM "<<target<<" TIDAK DITEMUKAN!\n\n";

	}

}

void menu_search(){

	int n;

	cout<<"\n3.1. Cari Nama\n3.2. Cari NIM\n3.3. Cari Nilai Tertinggi\n3.4. Cari Nilai Terendah\n";
	cout<<"Pilih : 3.";
	cin>>n;cin.ignore(); //cin.ignore() supaya bisa masukkan nama dengan spasi

	switch(n){

		case 1:{

			string target;

			cout<<"Nama yang dicari\t: ";getline(cin,target);	//getline supaya bisa nama berspasi

			name_search(target);

			break;

		}

		case 2:{

			long int target;

			cout<<"NIM yang dicari\t: ";cin>>target;

			nim_search(target);

			break;

		}

		case 3:{ //semua data dibawah sudah didapat oleh statistic_pull()

			cout<<"\nNilai tertinggi terdapat pada kelas "<<data.kelas[data.global_max_address].nama<<"\n";

			cout<<"Oleh "<<data.kelas[data.global_max_address].max_achieve<<" ("<<data.kelas[data.global_max_address].max_achieve_nim<<")\n";

			cout<<"Dengan nilai "<<data.global_max<<endl<<endl;

			break;

		}

		case 4:{

			cout<<"\nNilai terendah terdapat pada kelas "<<data.kelas[data.global_min_address].nama<<"\n";

			cout<<"Oleh "<<data.kelas[data.global_min_address].min_achieve<<" ("<<data.kelas[data.global_min_address].min_achieve_nim<<")\n";

			cout<<"Dengan nilai "<<data.global_min<<endl<<endl;

			break;

		}

	}

	menu();

}

void menu_sort(){ //gak jadi
	int n;

	cout<<"1. Urutan kelas berdasar banyak mahasiswa (descending)\n2. Urutan kelas berdasar nilai (descending)\n3. Urutan kelas berdasar rata-rata (descending)/n4. Urutan kelas berdasar simpangan baku (ascending)\n";

	cin>>n;

	switch(n)
	{

		case 1:
		{



			break;

		}

	}

}

void simpan(){	//fungsi simpan ke .txt

	ofstream out;

	out.open("Data Mahasiswa.txt");

	for(int i=0;i<data.banyak_kls;i++){

		out<<"=====KELAS "<<data.kelas[i].nama<<"======"<<endl;	//penunjukkan kelas

		for(int j=0;j<data.kelas[i].banyak_mhs;j++){

			out<<"Nama\t: "<<data.kelas[i].mhs[j].nama<<endl;

			out<<"NIM\t: "<<data.kelas[i].mhs[j].nim<<endl;

			out<<"Nilai\t: "<<data.kelas[i].mhs[j].nilai<<endl<<endl;

		}

	}

	out.close();

	cout<<"\n=====Data Telah Tersimpan=====";

	menu();

}

void keluar()
{
    cout<<"========================================================================"<<endl;
    cout<<"************************************************************************"<<endl;
    cout<<"*                      SEMOGA SUKSES!                                  *"<<endl;
    cout<<"************************************************************************"<<endl;
    cout<<"========================================================================"<<endl;
    cout<<"========================================================================"<<endl;
    cout<<"||                                                                    ||"<<endl;
    cout<<"||                      SAMPAI JUMPA                                  ||"<<endl;
    cout<<"||                                                                    ||"<<endl;
    cout<<"========================================================================"<<endl;
    cout<<endl<<endl;
    cout<<" _______________________________________________"<<endl;
    cout<<"|   Created by :                                |"<<endl;
    cout<<"| 1. Ramanda Walbari Ashar (123170107)          |"<<endl;
    cout<<"| 2. Yudhistira Tribuana Authar (123170109)     |"<<endl;
    cout<<"| 3. Sofura Mariah Nadita (123170110)           |"<<endl;
    cout<<"|_______________________________________________|"<<endl;
    
}

void menu()
{
	int n;

	if(data.banyak_kls==0)cout<<"1. Input Data\n    (Silahkan isi 1)";
	else cout<<"      MENU PROGRAM\n1. Input Data/Ubah Data \n2. Tampilkan Data\n3. Pencarian\n4. Simpan\n5. Keluar";
	cout<<"\nPilih : ";
	cin>>n;
	cout<<endl;
	cout<<"************************************************************************"<<endl;


	switch(n){

		case 1: menu_kelas();break;

		case 2: menu_tampil();break;

		case 3: menu_search();break;

		case 4: simpan();break;

		case 5: keluar();break;

	}

}

void statistic_pull(int n){

	struct_mhs score_sorted_temp[data.kelas[n].banyak_mhs];	//simpan struct_mhs kelas yang ditunjuk dalam array sementara

	for(int i=0;i<data.kelas[n].banyak_mhs;i++)	score_sorted_temp[i]=data.kelas[n].mhs[i]; //pemasukkan data ke array sementara

	class_score_bub_sort(n,score_sorted_temp); //pengurutan array sementara

	data.kelas[n].max=score_sorted_temp[data.kelas[n].banyak_mhs-1].nilai;	//karena sudah terurut, maka max adalah array tertinggi

	data.kelas[n].min=score_sorted_temp[0].nilai;	//sama, tapi terendah

	data.kelas[n].med=score_sorted_temp[data.kelas[n].banyak_mhs/2].nilai;	//sama, tapi banyak_mahasiswa / 2

	int current_mod=0,mod_counter=1;	//current_mod adalah penghitung modus saat ini, modus_counter untuk penghitung nilai sama dalam perulangan

	data.kelas[n].mod=data.kelas[n].mhs[0].nilai;	//anggap array 0 adalah modulus. Mulai perulangan dari array 1

	for(int i=1;i<data.kelas[n].banyak_mhs-1;i++){ //mulai dari 1 sampai banyak_mhs-1

		if(data.kelas[n].mhs[i].nilai==data.kelas[n].mhs[i+1].nilai){

			mod_counter++; //jika sama dengan sampingnya, maka modus counter +1

		}

		else if(mod_counter>current_mod){ //jika modus counter lebih besar dari modus saat ini

			data.kelas[n].mod=data.kelas[n].mhs[i].nilai; //masukkan nilai yang ditunjuk ke modus kelas

			current_mod=mod_counter;	//modus saat ini adalah modus counter

			mod_counter=0;	//modus counter ulang dari 0

		}

	}

	data.kelas[n].std_dev=0; //simpangan baku kelas yang ditunjuk(n) isi 0

	for(int i=0;i<data.kelas[n].banyak_mhs;i++){

		data.kelas[n].std_dev+=pow(data.kelas[n].mhs[i].nilai-data.kelas[n].mean,2); //tiap perulangan, ditambah (nilai-mean)^2

	}

	data.kelas[n].std_dev=sqrt(data.kelas[n].std_dev/data.kelas[n].banyak_mhs); //diakar kuadrat nilai std_dev/banyak_mhs

	if(data.kelas[n].max>data.global_max){ //jika max kelas > max global (seluruh kelas)

		data.global_max=data.kelas[n].max; //jadi max global baru

		data.global_max_address=n; //tunjuk kelas yang mangandung max global

	}

	if(data.kelas[n].min<data.global_min){ //sama, tapi minimal

		data.global_min=data.kelas[n].min;

		data.global_min_address=n;

	}

	data.kelas[n].max_achieve=score_sorted_temp[data.kelas[n].banyak_mhs-1].nama; //nama peraih max kelas itu

	data.kelas[n].max_achieve_nim=score_sorted_temp[data.kelas[n].banyak_mhs-1].nim; //nim peraih max kelas itu

	data.kelas[n].min_achieve=score_sorted_temp[0].nama;	//sama, tapi peraih min

	data.kelas[n].min_achieve_nim=score_sorted_temp[0].nim;	//sama, tapi peraih min

	data.total_mhs+=data.kelas[n].banyak_mhs;
}

void masuk_data(int n){

	cout<<"\nBanyak Mahasiswa    : ";cin>>data.kelas[n].banyak_mhs;cin.ignore(); //ditanya berapa banyak mahasiswa

	data.kelas[n].mean=0; //anggap mean 0

	for(int i=0;i<data.kelas[n].banyak_mhs;i++){

		cout<<"Nama\t: ";getline(cin,data.kelas[n].mhs[i].nama); //nama berspasi. pakai getline

		cout<<"NIM\t: ";cin>>data.kelas[n].mhs[i].nim;

		cout<<"Nilai\t: ";cin>>data.kelas[n].mhs[i].nilai;

		cout<<endl;cin.ignore(); //cin.ignore(), agar bisa pakai getline nanti

		data.kelas[n].mean+=data.kelas[n].mhs[i].nilai; //setiap masuk data, mean bertambah sesuai nilai yang dimasukkan

	}

	data.kelas[n].mean/=data.kelas[n].banyak_mhs; //mean dibagi banyak mahasiswa. dapat rata-rata

	statistic_pull(n); //panggil fungsi untuk mengisi variable-variable statistik. parameter n adalah kelas yang ditunjuk

}

void tambah_kelas(){

	cout<<"\nNama Kelas\t: ";cin>>data.kelas[data.banyak_kls].nama; //memasukkan nama kelas (1 karakter!)
	masuk_data(data.banyak_kls);	//merubah data kelas pada alamat banyak kelas saat ini (kelas terbaru)

	data.banyak_kls++; //setelah selesai, banyak kelas bertambah agar siap menerima kelas baru selanjutnya

	menu(); //kembali ke menu

}

void tampil_data(int n){
    cout<<"====TAMPILAN DATA===="<<endl;
	for(int i=0;i<data.kelas[n].banyak_mhs;i++){

		cout<<"Nama\t: "<<data.kelas[n].mhs[i].nama<<endl;

		cout<<"NIM\t: "<<data.kelas[n].mhs[i].nim<<endl;

		cout<<"Nilai\t: "<<data.kelas[n].mhs[i].nilai<<endl;

		cout<<endl;

	}

    cout<<"====DATA STATISTIK KELAS===="<<endl;
	cout<<"Mean\t: "<<data.kelas[n].mean<<endl;

	cout<<"Minimal\t: "<<data.kelas[n].min<<endl;

	cout<<"Maximal\t: "<<data.kelas[n].max<<endl;

	cout<<"Modus\t: "<<data.kelas[n].mod<<endl;

	cout<<"Standar Deviasi\t: "<<data.kelas[n].std_dev<<endl<<endl;

}

void menu_kelas(){

	int pilih;

	cout<<"\n1.1 Tambah Kelas\n"; //selalu muncul

	for(int i=0;i<data.banyak_kls;i++){ //kalau ada kelas, menu bertambah untuk menunjukkan kelas

		cout<<"1."<<i+2<<" Kelas "<<data.kelas[i].nama<<endl;

	}
    cout<<"Pilih : 1.";
	cin>>pilih;

	if(pilih==1){

		tambah_kelas(); //fungsi tambah kelas baru

	}

	else if(pilih-1>data.banyak_kls){

		cout<<"Kelas belum terdaftar!\n\n"; //jika kelas yang ditunjuk belum dibuat

	}

	else{

		masuk_data(pilih-2); //merubah data yang telah ada. kayaknya bisa

	}

	menu();

}
void tampil_global(){
	data.global_mean=0.0;
	for(int i=0;i<data.banyak_kls;i++)
    {
		data.global_mean+=data.kelas[i].mean;
	}
	data.global_mean/=data.banyak_kls;
	cout<<endl;
	cout<<"===TAMPILAN DATA SELURUH KELAS==="<<endl;
	cout<<" Global mean\t: "<<data.global_mean<<endl;
	cout<<" Global max\t: "<<data.global_max<<endl;
	cout<<" Global min\t: "<<data.global_min<<endl;
	cout<<" Banyak mahasiswa total: "<<data.total_mhs<<endl;
	cout<<endl;
}
void menu_tampil(){
	int pilih;
	cout<<"\n1.1. Data statistik seluruh kelas\n";
	for(int i=0;i<data.banyak_kls;i++){ //sama kayak menu diatas. kalau ada kelas, tampilkan. jika tidak, menu kosong.
		cout<<"1."<<i+2<<" Kelas "<<data.kelas[i].nama<<endl;
	}
	cout<<"Pilih : 1.";
	cin>>pilih;
	if(pilih==1)tampil_global();
	else tampil_data(pilih-2);	//fungsi tampilkan data yang dipilih
	menu();
}

int main()
{
	cout<<"           =========================================================="<<endl;
	cout<<"           =             APLIKASI STATISTIKA MAHASISWA              ="<<endl;
	cout<<"           =                 UPN VETERAN YOGYAKARTA                 ="<<endl;
	cout<<"           =========================================================="<<endl;
	cout<<endl<<endl;
	cout<<"   MENU PROGRAM"<<endl;
	cout<<" 1. Input Data"<<endl;
	cout<<" 2. Tampilkan Data"<<endl;
	cout<<" 3. Pencarian"<<endl;
	cout<<" 4. Simpan"<<endl;
	cout<<" 5. Keluar"<<endl;
	cout<<"NOTE : Pada program ini, wajib input data terlebih dahulu!"<<endl;
	cout<<endl;
	menu();

}

