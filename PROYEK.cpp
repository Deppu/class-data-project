#include<iostream>
using namespace std;
struct struct_mhs{
	string nama;
	long int nim;
	int nilai;
};
struct struct_kelas{
	int banyak_mhs;
	char nama;
	struct_mhs mhs[64];
};
struct {
	int banyak_kls=0;
	struct_kelas kelas[64];
}data;
void menu_kelas();
void menu_tampil();
void menu(){
	int n;
	cout<<"1. Masukkan/Ubah Data\n2. Tampilkan Data\n";cin>>n;
	switch(n){
		case 1: menu_kelas();break;
		case 2: menu_tampil();break;
	}
}
void masuk_data(int n){
	cout<<"\nBanyak Mahasiswa\t: ";cin>>data.kelas[n].banyak_mhs;cin.ignore();
	for(int i=0;i<data.kelas[n].banyak_mhs;i++){
		cout<<"Nama\t: ";getline(cin,data.kelas[n].mhs[i].nama);
		cout<<"NIM\t: ";cin>>data.kelas[n].mhs[i].nim;
		cout<<"Nilai\t: ";cin>>data.kelas[n].mhs[i].nilai;
		cout<<endl;cin.ignore();
	}
}
void tambah_kelas(){
	cout<<"\nNama Kelas\t: ";cin>>data.kelas[data.banyak_kls].nama;
	masuk_data(data.banyak_kls);
	data.banyak_kls++;
	menu();
}
void tampil_data(int n){
	for(int i=0;i<data.kelas[n].banyak_mhs;i++){
		cout<<"Nama\t: "<<data.kelas[n].mhs[i].nama<<endl;
		cout<<"NIM\t: "<<data.kelas[n].mhs[i].nim<<endl;
		cout<<"Nilai\t: "<<data.kelas[n].mhs[i].nilai<<endl;
		cout<<endl;
	}
}
void menu_kelas(){
	int pilih;
	cout<<"\n1.1 Tambah Kelas\n";
	for(int i=0;i<data.banyak_kls;i++){
		cout<<"1."<<i+2<<" Kelas "<<data.kelas[i].nama<<endl;
	}
	cin>>pilih;
	if(pilih==1){
		tambah_kelas();
	}
	else if(pilih-1>data.banyak_kls){
		cout<<"Kelas belum terdaftar!\n\n";
	}
	else{
		masuk_data(pilih-2);
	}
	menu();
}
void menu_tampil(){
	int pilih;
	cout<<"\n";
	for(int i=0;i<data.banyak_kls;i++){
		cout<<"1."<<i+1<<" Kelas "<<data.kelas[i].nama<<endl;
	}
	cin>>pilih;
	tampil_data(pilih-1);
	menu();
}
int main(){
	menu();
}
