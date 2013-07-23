void md_find_media();
void md_scan_media(DIR *target_dir, struct dirent *ep);
const char *get_file_ext(const char *filename);
void md_check_file(struct dirent *ep);

const char *SUPPORTED_FORMATS[] = {"mkv","avi"};