#include <stdio.h>
#include <math.h>

#define USERS 5
#define MOVIES 4

void display_ratings();
float similarity(int user1, int user2);
float predict_rating(int user, int movie);
void recommend_movies(int user);
void display_similarities();

int ratings[USERS][MOVIES] = {
    {5, 3, 4, -1},
    {4, 2, -1, 5},
    {3, 5, 4, -1},
    {5, -1, 3, 4},
    {-1, 4, 2, 5}
};

void display_ratings() {
    printf("User-Movie Rating Matrix:\n");
    printf("    M1  M2  M3  M4\n");
    for (int i = 0; i < USERS; i++) {
        printf("U%d ", i + 1);
        for (int j = 0; j < MOVIES; j++) {
            if (ratings[i][j] == -1)
                printf("  - ");
            else
                printf("  %d ", ratings[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

float similarity(int user1, int user2) {
    float dot = 0, norm1 = 0, norm2 = 0;
    for (int i = 0; i < MOVIES; i++) {
        if (ratings[user1][i] != -1 && ratings[user2][i] != -1) {
            dot += ratings[user1][i] * ratings[user2][i];
            norm1 += ratings[user1][i] * ratings[user1][i];
            norm2 += ratings[user2][i] * ratings[user2][i];
        }
    }
    if (norm1 == 0 || norm2 == 0) return 0;
    return dot / (sqrt(norm1) * sqrt(norm2));
}

void display_similarities() {
    printf("User Similarity Matrix:\n");
    printf("      U1   U2   U3   U4   U5\n");
    for (int i = 0; i < USERS; i++) {
        printf("U%d ", i + 1);
        for (int j = 0; j < USERS; j++) {
            if (i == j)
                printf("  -  ");
            else
                printf(" %.2f ", similarity(i, j));
        }
        printf("\n");
    }
    printf("\n");
}


float predict_rating(int user, int movie) {
    float weighted_sum = 0, sim_sum = 0;
    for (int i = 0; i < USERS; i++) {
        if (i != user && ratings[i][movie] != -1) {
            float sim = similarity(user, i);
            weighted_sum += sim * ratings[i][movie];
            sim_sum += fabs(sim);
        }
    }
    return (sim_sum == 0) ? 0 : (weighted_sum / sim_sum);
}

void recommend_movies(int user) {
    printf("Recommended Movies for User %d:\n", user + 1);
    int recommended = 0;
    for (int i = 0; i < MOVIES; i++) {
        if (ratings[user][i] == -1) {
            float predicted = predict_rating(user, i);
            printf("Movie %d (Predicted Rating: %.2f)\n", i + 1, predicted);
            recommended = 1;
        }
    }
    if (!recommended) {
        printf("No recommendations available.\n");
    }
    printf("\n");
}

int main() {
    display_ratings();
    display_similarities();
    for (int user = 0; user < USERS; user++) {
        recommend_movies(user);
    }
    return 0;
}
