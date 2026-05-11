/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
 *   Modul               : 05 - Foundation of Algorithm
 *   Hari dan Tanggal    : Senin, 11 Mei 2026
 *   Nama (NIM)          : Fesya Dea Azzahra (13224049)
 *   Nama File           : soal2_Modul5.c
 *   Deskripsi           : Sistem harus memastikan bahwa seluruh misi memang dapat diselesaikan tanpa konflik ketergantungan melingkar. 
 *                         Menentukan apakah susunan prasyarat yang diberikan masih memungkinkan semua misi dijalankan.
 *                         1. Ada N misi bernomor 0..N-1
                           2. Ada M pasangan a b, artinya a bergantung pada b
                           3. Semua misi bisa diselesaikan jika graph dependensi tidak memiliki siklus
 *                         I : N M a1 b1 a2 b2 ... aM bM
                               misal : 3 3 1 0 2 1 0 2
 *                         O : BISA atau TIDAK BISA
                               misal : BISA
 */
// Soal 2: Jadwal Misi Bertabrakan 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MISI 50
#define MAX_DEPENDENSI 100

typedef struct Misi {
    int misi[MAX_MISI];
    int prasyarat[MAX_DEPENDENSI];
} Misi;

int dfs (Misi *misi, int node, int visited[], int recStack[]) {  //Fungsi untuk melakukan Depth First Search (DFS) pada graph dependensi untuk mendeteksi siklus
    if (visited[node] == 0) {   //Jika node belum dikunjungi, maka tandai sebagai dikunjungi dan tambahkan ke recursion stack
        visited[node] = 1;
        recStack[node] = 1;
        for (int i = 0; i < MAX_DEPENDENSI; i++) {   //Iterasi melalui semua prasyarat dari node saat ini
            int prasyaratNode = misi->prasyarat[i];
            if (prasyaratNode == -1) {   
                break;
            }
            if (!visited[prasyaratNode] && dfs(misi, prasyaratNode, visited, recStack)) {   
                return 1;
            } else if (recStack[prasyaratNode]) {    
                return 1;
            }
        }
    }
    recStack[node] = 0;   //Hapus node dari recursion stack sebelum kembali
    return 0;   //Tidak ada siklus ditemukan
}
int konflikMelingkar (Misi *misi, int N, int M) {
    int visited[MAX_MISI] = {0};
    int recStack[MAX_MISI ] = {0};
    for (int i = 0; i < N; i++) {
        if (dfs(misi, i, visited, recStack)) {
            return 1;
        }
    }
    return 0;
}

int main () {
    int N, M;
    scanf("%d %d", &N, &M);
    Misi misi;
    memset(misi.prasyarat, -1, sizeof(misi.prasyarat));  
        int a, b;
        scanf("%d %d", &a, &b);
        misi.prasyarat[a] = b; 
    if (konflikMelingkar(&misi, N, M)) {
        printf("BISA\n");
    } else {
        printf("TIDAK BISA\n");
    }
    return 0;
}
