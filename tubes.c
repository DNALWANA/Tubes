#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>


int pilih,km,saldo = 0;
int menuUser,nominal;
char usr[30],passusr[30];

struct {
    char nama[100],email[100],telepon[100],alamat[100],nik[16],username[100],password[100],userID [50];
    int infoSaldo;
}DataUser;

void admin();
void user1();
void usermenu();
void depo();
void divider();
void detail();
void wduser();
void loadsaldo();
void savesaldo();
void dpwd();
void membership();
void tampilkan_daftar_bank();
void lanjutkan_proses(int pil);
void transfer();
void daftar_user();
int login_user();
int login_admin();







//=============FUNGSI PENDUKUNG==============

void divider(){
    printf("---------------------------\n");
}

void loadsaldo(){

FILE *file = fopen("money.txt","r");
if (file != NULL) {
    fscanf(file, "%d", &DataUser.infoSaldo);
    fclose(file);
    } else 
    {
        saldo = 0; 
    }
}

void savesaldo(){
    FILE *file = fopen("money.txt", "w");
    if (file != NULL) 
    {
        fprintf(file, "%d", DataUser.infoSaldo);
        fclose(file);
    }
}

enum pilih{
    YES,
    NO,
    INVALID,
};

enum pilih stringtonum(const char *input){

    if (strcmp(input, "Yes")== 0) return YES;
    else if (strcmp(input, "No")== 0) return NO;
    else return INVALID;
}
void tampilkan_daftar_bank();
void lanjutkan_proses(int pilihan);

//===================================================


int main(){

    loadsaldo();
    system("cls");
    int pilihan;
    int mode;

    while (1) {
        printf("\nSilahkan pilih role akun:\n");
        printf("1. Admin\n");
        printf("2. Customer\n");
        printf("3. Exit\n");
        printf("Pilih role: ");
        scanf("%d", &mode);
        getchar();

        if (mode == 1) {
            if (login_admin()) {
                printf("Akses menu admin...\n");  //nyambung ke codingan fitur fitur admin
            }
        } else if (mode == 2) {
            printf("\nSilahkan pilih menu yang tersedia\n");
            printf("1. Daftar akun\n");
            printf("2. Login akun\n");
            printf("Pilih menu (1-2): ");
            scanf("%d", &pilihan);
            getchar(); 
            switch (pilihan) {
                case 1:
                    daftar_user();
                    break;
                case 2:
                    login_user();
                    break;
                default:
                    printf("Pilihan tidak tersedia, silahkan pilih menu yang ada (1-2).\n");
            }
        } else if (mode == 3) {
            printf("Menyimpan data dan keluar dari program...\n");
            exit(0);
        } else {
            printf("Pilihan mode tidak valid. Silakan pilih 1, 2, atau 3.\n");
        }
    }
    return 0;
}

void daftar_user() {
    FILE *file = fopen("users.txt", "a");

    if (!file) {
        printf("Gagal membuka file.\n");
        return;
    }
    printf("Menu daftar akun (user)\n");
    printf("Masukkan Nama: ");
    fgets(DataUser.nama, sizeof(DataUser.nama), stdin);
    DataUser.nama[strcspn(DataUser.nama, "\n")] = 0;
    printf("Masukkan No ID: ");
    fgets(DataUser.userID, sizeof(DataUser.userID), stdin);
    DataUser.userID[strcspn(DataUser.userID, "\n")] = 0;
    printf("Masukkan Email: ");
    fgets(DataUser.email, sizeof(DataUser.email), stdin);
    DataUser.email[strcspn(DataUser.email, "\n")] = 0;
    printf("Masukkan No Telepon (contoh : 08..........): ");
    fgets(DataUser.telepon, sizeof(DataUser.telepon), stdin);
    DataUser.telepon[strcspn(DataUser.telepon, "\n")] = 0;
    printf("Masukkan Alamat Rumah (Contoh : JL.Padat Karya): ");
    fgets(DataUser.alamat, sizeof(DataUser.alamat), stdin);
    DataUser.alamat[strcspn(DataUser.alamat, "\n")] = 0;
    printf("Masukkan NIK: ");
    fgets(DataUser.nik, sizeof(DataUser.nik), stdin);
    DataUser.nik[strcspn(DataUser.nik, "\n")] = 0;
    printf("Masukkan Password: ");
    fgets(DataUser.password, sizeof(DataUser.password), stdin);
    DataUser.password[strcspn(DataUser.password, "\n")] = 0;

    fprintf(file, "%s|%s|%s|%s|%s|%s|%s\n",
        DataUser.nama, DataUser.userID, DataUser.email, DataUser.telepon, DataUser.alamat, DataUser.nik, DataUser.password);

    fclose(file);
    printf("Registrasi berhasil, Silahkan ke menu Login :)\n");
}

int login_user() {
    char userID[50], nik[20], password[50];
    char buffer[600];
    FILE *file = fopen("users.txt", "r");

    if (!file) {
        printf("File tidak tersedia.\n");
        return 0;
    }

    printf("Menu Login User\n");
    printf("No ID: ");
    fgets(userID, sizeof(userID), stdin);
    userID[strcspn(userID, "\n")] = 0;

    printf("NIK: ");
    fgets(nik, sizeof(nik), stdin);
    nik[strcspn(nik, "\n")] = 0;

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%99[^|]|%49[^|]|%99[^|]|%19[^|]|%199[^|]|%19[^|]|%49[^\n]",
               DataUser.nama, DataUser.userID, DataUser.email, DataUser.telepon, DataUser.alamat, DataUser.nik, DataUser.password);

        if (strcmp(DataUser.userID, userID) == 0 &&
            strcmp(DataUser.nik, nik) == 0 &&
            strcmp(DataUser.password, password) == 0) {
            printf("Login berhasil. Selamat datang, %s!\n", DataUser.nama); //nyambung ke fitur user
            fclose(file);
            usermenu();
            return 1;
        }
    }
    fclose(file);
    printf("Login tidak berhasil. No ID, NIK, atau Password anda salah.\n");
    return 0;
}

int login_admin() {
    char id[50], password[50];

    printf("Menu Login Admin\n");
    printf("ID Admin: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    printf("Password Admin: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(id, "101042400019") == 0 && strcmp(password, "dbank") == 0) {
        printf("Login berhasil, selamat datang Admin!!!\n");
        return 1;
    } else {
        printf("Login gagal, ID atau Password salah.\n");
        return 0;
    }
}


void usermenu(){

    int pilih3;
    int pil;
    system("cls");
    tampilkan_daftar_bank();
    scanf("%d", &pil);
    lanjutkan_proses(pil);

    printf("=== MAIN MENU ===\n");
    divider();

    printf("1.Deposit & Withdraw Money\n");
    printf("2.Membership\n");
    printf("3.Transfer\n");
    printf("4.Transaction Detail\n");
    printf("5.Logout\n");
    printf("Pilih: ");
    scanf("%d", &pilih3);getchar();

    switch (pilih3)
    {
        case 1:
        dpwd();
        break;

        case 2:
        membership();
        break;

        case 3:
        transfer();
        break;

        case 4:
        detail();
        break;

        case 5:
        main();
        break;
    
        default:
        printf("Input tidak valid\n");
        system("pause");
        usermenu();
        break;
    }
}


void dpwd(){
system("cls");
char chose[30];

printf("== DEPOSIT & WITHDRAW MONEY ==\n");
divider();

printf("Apakah ingin menyimpan uang?\n");
printf("(Yes (Deposit)\n");
printf("(No (Withdraw)\n");
printf("Pilih: ");
fgets(chose,sizeof(chose),stdin);
chose[strcspn(chose, "\n")] = '\0';

switch (stringtonum(chose))
{
case YES:
    depo();
    break;

case NO:
    wduser();
    break;

default:
    printf("Pilihan tidak valid\n");
    system("pause");
    usermenu();
    break;
}
}


void depo(){

    system("cls");
    int ju;
    time_t tm;
    time(&tm);

    FILE *aw = fopen("notif.txt","a");

    printf("=== DEPOSIT MONEY ===\n");
    divider();

    printf("Silahkan memasukan jumlah uang deposit\n");
    printf("Masukan jumlah deposit: ");
    scanf("%d", &ju);

    DataUser.infoSaldo += ju;
    savesaldo();

    printf("Pengisian saldo sebesar Rp%d pada %s dimasukan dalam rekeningmu\n",ju,ctime(&tm));
    fprintf(aw,"Kamu mengisi saldo sebesar %d pada %s\n",ju, ctime(&tm));

    fclose(aw);
    system("pause");
    usermenu();
}

void wduser(){

    int wd;
    system("cls");

    time_t tm;
    time(&tm);

    FILE *aw;
    aw = fopen("notif.txt","a");
    
    printf("== WITHDRAW MONEY ==\n");
    divider();

    printf("Masukan jumlah saldo yang ingin di withdraw: ");
    scanf("%d",&wd);

    if (wd > DataUser.infoSaldo)
    {
       printf("Saldo anda tidak mencukupi untuk withdraw\n");
       system("pause");
       usermenu();
       return;
    }else
    {
    DataUser.infoSaldo -= wd;
    savesaldo();

    printf("Withdraw saldo sebesar %d pada %s terkonfirmasi\n",wd,ctime(&tm));
    fprintf(aw,"Anda withdraw saldo sebanyak %d pada %s telah terkonfirmasi\n",wd,ctime(&tm));

    fclose(aw);
    system("pause");
    usermenu();
    }
}

void membership(){
    int bonus = 0;
    
    FILE *aw = fopen("notif.txt","a");


    system("cls");

    printf("=== MENU USER - MEMBERSHIP ===\n");
    divider();
    
    if (DataUser.infoSaldo >= 5000000 && DataUser.infoSaldo <=10000000){
        printf("SELAMAT ANDA MENJADI MEMBERSHIP -BASIC-\n");
        bonus = 5000;
        DataUser.infoSaldo += bonus;
        printf("Anda mendapatkan bonus MEMBERSHIP BASIC sebanyak %d ditambahkan ke rekening anda!!\n",bonus);
        fprintf(aw,"Anda mendapatkan bonus MEMBERSHIP BASIC sebanyak %d ditambahkan ke rekening anda\n",bonus);

    }else if(DataUser.infoSaldo > 10000000 && DataUser.infoSaldo <=20000000){
        printf("SELAMAT ANDA MENJADI MEMBERSHIP -SILVER-\n");
        bonus = 10000;
        DataUser.infoSaldo += bonus;
        printf("Anda mendapatkan bonus MEMBERSHIP SILVER sebanyak %d ditambahkan ke rekening anda!!\n",bonus);
        fprintf(aw,"Anda mendapatkan bonus MEMBERSHIP SILVER sebanyak %d ditambahkan ke rekening anda\n",bonus);

    }else if(DataUser.infoSaldo > 20000000){
        printf("SELAMAT ANDA MENJADI MEMBERSHIP -GOLD-\n");
        bonus = 15000;
        DataUser.infoSaldo += bonus;
        printf("Anda mendapatkan bonus MEMBERSHIP GOLD sebanyak %d ditambahkan ke rekening anda!!\n",bonus);
        fprintf(aw,"Anda mendapatkan bonus MEMBERSHIP GOLD sebanyak %d ditambahkan ke rekening anda\n",bonus);

    }else{
        printf("MOHON MAAF ANDA BELUM MENJADI MEMBERSHIP\n");
        bonus = 0;
    }

    printf("Total pendapatan bonus membership: %d\n",bonus);
    printf("Total saldo anda: %d\n",DataUser.infoSaldo);

    fclose(aw);
    system("pause");
    usermenu();
}

void transfer(){
    
    char buffer[100];
    char tujuanID[100];
    bool valid = false;
    FILE * fuser;
    printf("\n=== MENU USER - TRANSFER ===\n");
    printf("Masukkan ID user Tujuan: ");
    scanf("%s", tujuanID);

    fuser = fopen("user.txt", "r");
    while (fgets(buffer, sizeof(buffer), fuser)){
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(tujuanID, buffer) == 0) {
            valid = true;
            break;
        }
    }

    fclose(fuser);

    if (!valid) {
        printf("ID user tujuan tidak ditemukan!\n");
        return;
    }

    printf("Masukkan nominal yang ingin anda transfer : Rp");
    scanf("%d",&nominal);

    if (nominal <= 0 || nominal > DataUser.infoSaldo) {
        printf("Transfer gagal. Nominal tidak valid atau saldo tidak cukup.\n");
        return;
    }

    DataUser.infoSaldo -= nominal;
    printf("\n-------------------------------\n");
    printf("Selamat %d berhasil ditransfer ke Nomor Rekening %d\n",nominal, tujuanID);
    printf("Sisa Saldo Anda : %d\n", DataUser.infoSaldo);
    system("pause");
    main();
}


void detail(){
    system("cls");

    FILE *aw;
    aw = fopen("notif.txt","r");
    char d = fgetc(aw);
    int Empty = 1;;

    printf("== TRANSACTION DETAIL ==\n");
    divider();

    while ((d = fgetc(aw)) != EOF) {
        putchar(d); 
        Empty = 0; 
    }
    if (Empty) {
        printf("Data kosong\n");
    }

    fclose(aw); 
    system("pause");
    usermenu();
}



void tampilkan_daftar_bank() {
    printf("=== PILIH TIPE BANK ===\n");
    printf("1. MANDIRI\n");
    printf("2. BCA\n");
    printf("3. BNI\n");
    printf("4. CIMB NIAGA\n");
    printf("5. BRI\n");
    printf("Masukkan pilihan (1-5): ");
}

void lanjutkan_proses(int pil) {
    switch(pil) {
        case 1:
            system("color 06");
            printf("Kamu memilih bank MANDIRI\n");
            break;
        case 2:
            system("color 09");
            printf("Kamu memilih bank BCA\n");
            break;
        case 3:
            system("color 0A");
            printf("Kamu memilih bank BNI\n");
            break;
        case 4:
            system("color 0C");
            printf("Kamu memilih bank CIMB NIAGA\n");
            break;
        case 5:
            system("color 0F");
            printf("Kamu memilih bank BRI\n");
            break;
        default:
            system("color 0C");
            printf("Pilihan tidak tersedia!\n");
    }
}