#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
    FILE *fp;
    if ((fp = fopen("net.cap", "rb")) == NULL) {
        printf("Can't open net.cap.\n");
        return 1;
    } else {
        // Parse the global header
        char global_header[24];
        fread(global_header, sizeof(global_header), 1, fp);

        uint32_t magic_number, snapshot_length;
        uint32_t major_version, minor_version;

        memcpy(&magic_number, global_header, 4);
        memcpy(&major_version, global_header + 4, 2);
        memcpy(&minor_version, global_header + 6, 2);
        memcpy(&snapshot_length, global_header + 16, 4);

        printf("### GLOBAL HEADER ###\n");
        printf("Magic number:       %d\n", magic_number);
        printf("Major version:      %d\n", major_version);
        printf("Minor version:      %d\n", minor_version);
        printf("Snapshot length:    %d\n", snapshot_length);
        printf("-------------------------\n");

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
               printf("Packet len and untrunc len do not match.\n"); 
            }


            // Parse the packet data
            char packet_data[packet_length];
            fread(packet_data, packet_length, 1, fp);

            if (sizeof(packet_header) > 0 && sizeof(packet_data) > 0) {
                packet_count++;
            }

        }
        printf("Total packet count: %d\n", packet_count);


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
