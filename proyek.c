#include <stdio.h>
#define JUMLAH_HARI 7
int target = 10000;

typedef struct DataHarian{
    char hari[10];
    int jmlLangkah;
    int progress;
} DataHarian;

void inputData(DataHarian *data);

void calcProgress(int target, DataHarian *data);
int calcTotalLangkah(DataHarian *data);
int jmlHariTercapai(int target, DataHarian *data);
int totalKekurangan(int target, DataHarian *data);

void printStatus(int target, DataHarian data);
void printProgressHarian(int target, DataHarian *data);


void printHariTercapai(int target, DataHarian *data);
void printBestAndWorstDay(DataHarian *data);
void printStatusMingguIni(int target, DataHarian *data);
void printProgressMingguan(int target, DataHarian *data);

int main() {

    DataHarian data[7] = { 
        {"Senin"}, 
        {"Selasa"}, 
        {"Rabu"}, 
        {"Kamis"}, 
        {"Jumat"}, 
        {"Sabtu"}, 
        {"Minggu"} 
    };

    printf("\n======= TRACKER LANGKAH HARIAN =======\n");
    printf("Target Harian: 10.000 langkah\n");
    printf("INPUT LANGKAH HARIAN:\n");
    inputData(data);
    calcProgress(target, data);
    printProgressHarian(target, data);
    printProgressMingguan(target, data);

    return 0;
}



void inputData(DataHarian *data) {
    for (int i = 0; i < JUMLAH_HARI; i++) {
        printf("%-8s: ", data[i].hari);
        scanf("%d", &data[i].jmlLangkah);
    }
}

void calcProgress(int target, DataHarian *data) {
    for (int i = 0; i < JUMLAH_HARI; i++) {
        data[i].progress = ((data[i].jmlLangkah) * 100) / target ;
    }
}

int calcTotalLangkah(DataHarian *data) {
    int total = 0;
    for (int i = 0; i < JUMLAH_HARI; i++) {
        total += (data[i].jmlLangkah);
    }
    return total;
}

int jmlHariTercapai(int target, DataHarian *data) {
    int daysReached = 0;
    for (int i = 0; i < JUMLAH_HARI; i++) {
        if (data[i].jmlLangkah >= target) {
            daysReached++;
        }
    }
    return daysReached;
}

int totalKekurangan(int target, DataHarian *data) {
    int langkahKekurangan = 0;
    for (int i = 0; i < JUMLAH_HARI; i++) {
        if (data[i].jmlLangkah < target) {
            langkahKekurangan += (target - data[i].jmlLangkah); 
        }
    }
    return langkahKekurangan;
}

void printStatus(int target, DataHarian data) {
     if (data.jmlLangkah < target) {
            printf("Kurang %d langkah\n", (target - (data.jmlLangkah)));
    } else if (data.jmlLangkah == target) {
        printf("TARGET TERCAPAI! tepat 10.000 langkah\n");
    } else {
        printf("TARGET TERCAPAI! +%d langkah\n", ((data.jmlLangkah) - target));
    }
}

void printProgressHarian(int target, DataHarian *data) {
    printf("\n======= PROGRES HARIAN =======\n");
    for (int i = 0; i < JUMLAH_HARI; i++) {
        printf("\n%s\n", data[i].hari);
        printf("Langkah  : %d\n", data[i].jmlLangkah);
        printf("Target   : %d\n", target);
        printf("Progress : %d%%\n", data[i].progress);
        printf("Status   : ");
        printStatus(target, data[i]);
    }
}

void printHariTercapai(int target, DataHarian *data) {
    int first = 1;

    for (int i = 0; i < JUMLAH_HARI; i++) {
        if (data[i].jmlLangkah >= target) {
            if (!first) {
                printf(", ");
            }
            printf("%s", data[i].hari);
            first = 0;
        }
    }
    printf("\n");
}

void printBestAndWorstDay(DataHarian *data) {
    int indexBest = 0;
    int indexWorst = 0;

    for (int i = 1; i < JUMLAH_HARI; i++) {
        if (data[i].jmlLangkah > data[indexBest].jmlLangkah) {
            indexBest = i;
        }
        if (data[i].jmlLangkah < data[indexWorst].jmlLangkah) {
            indexWorst = i;
        }
    }

    printf("\nHari terbaik           : %s (%d langkah)\n",
           data[indexBest].hari,
           data[indexBest].jmlLangkah);

    printf("Hari terburuk          : %s (%d langkah)\n",
           data[indexWorst].hari,
           data[indexWorst].jmlLangkah);
}


void printStatusMingguIni(int target, DataHarian *data) {
    int kekurangan = totalKekurangan(target, data);

    if (kekurangan <= 5000) {
        printf("Status minggu ini      : SANGAT BAIK\n");
    } else if (kekurangan <= 10000) {
        printf("Status minggu ini      : CUKUP BAIK\n");
    } else if (kekurangan <= 20000) {
        printf("Status minggu ini      : BAIK\n");
    } else if (kekurangan <= 30000) {
        printf("Status minggu ini      : CUKUP BURUK\n");
    } else if (kekurangan <= 50000) {
        printf("Status minggu ini      : BURUK\n");
    } else {
        printf("Status minggu ini      : SANGAT BURUK\n");
    }
}

void printProgressMingguan(int target, DataHarian *data) {
    int totalLangkah = calcTotalLangkah(data);
    printf("\n======= RINGKASAN MINGGU INI =======\n");

    printf("Total langkah          : %d\n", totalLangkah);
    printf("Target mingguan        : %d\n", target * 7);
    printf("Rata-rata harian       : %d\n", totalLangkah / 7);
    
    printf("\nHari target tercapai   : %d/7 hari (%d%%)\n", jmlHariTercapai(target, data), (jmlHariTercapai(target, data) * 100) / 7);
    printHariTercapai(target, data);
    printBestAndWorstDay(data);
    
    printf("\nTotal kekurangan       : %d\n", totalKekurangan(target, data));
    printStatusMingguIni(target, data);
}
