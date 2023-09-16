#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_packet_length(char header[]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Incorrect number of cmd line args.\n");
        return 1;
    }

    FILE *fp;
    if ((fp = fopen(argv[1], "rb")) == NULL) {
        printf("Can't open %s.\n", argv[1]);
        return 1;
    } else {
        // Parse the global header
        char global_header[24];
        fread(global_header, sizeof(global_header), 1, fp);

        // Our fp should be at the start of the packets
        // Each packet has a 16 byte header and variable length data
        int packet_length, untrunc_packet_length, packet_count = 0;
        while(!feof(fp)) {
            // Parse the packet header
            char packet_header[16];
            fread(packet_header, 16, 1, fp);
            // Get the packet length
            memcpy(&packet_length, packet_header + 8, 4);
            // Get the un-truncated packet length
            memcpy(&untrunc_packet_length, packet_header + 12, 4);

            if (packet_length != untrunc_packet_length) {
               printf("Packet len and untrunc len so not match.\n"); 
            }

            // Parse the packet data
            char packet_data[packet_length];
            fread(packet_data, packet_length, 1, fp);

            if (sizeof(packet_header) > 0 && sizeof(packet_data) > 0) {
                packet_count++;
            }

            // printf("packet length: %d\n", packet_length);
        }
        printf("packet count: %d\n", packet_count);


        /**
        for (size_t i = 0; i < sizeof(buffer); i++) {
            fprintf(stdout, "%02x ", buffer[i]);
            if ((i + 1) % 16 == 0) {
                fputc('\n', stdout);
            }
        }
        */
    }

    fclose(fp);
    return 0;
}

int get_packet_length(char header[]) {
    int len;
    memcpy(&len, header + 8, 4);
    return len;
}
