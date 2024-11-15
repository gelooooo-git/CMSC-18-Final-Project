void loadFunds() {
    FILE *file = fopen(FUNDS_FILE, "r");
    if (file != NULL) {
        fscanf(file, "%d", &total_funds);
        fclose(file);
    } else {
        printf("Funds file empty.\n");
        total_funds = 0; // Initialize funds if no file exists
    }
}

void saveFunds() {
    FILE *file = fopen(FUNDS_FILE, "w");
    if (file != NULL) {
        fprintf(file, "%d", total_funds);
        fclose(file);
    } else {
        printf("Funds file empty.\n");
    }
}

void fundsHistory(const char *action, int amount, const char *reason) {