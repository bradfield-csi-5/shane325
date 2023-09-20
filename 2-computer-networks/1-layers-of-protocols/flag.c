#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

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
        uint16_t major_version, minor_version;

        memcpy(&magic_number, global_header, 4);
        memcpy(&major_version, global_header + 4, 2);
        memcpy(&minor_version, global_header + 6, 2);
        memcpy(&snapshot_length, global_header + 16, 4);

        printf("### GLOBAL HEADER ###\n");
        printf("Magic number:       %u\n", magic_number);
        printf("Major version:      %u\n", major_version);
        printf("Minor version:      %u\n", minor_version);
        printf("Snapshot length:    %u\n", snapshot_length);
        printf("-------------------------\n");

        // Our fp should be at the start of our packets
        // Each packet has a 16 byte header and variable length data
        int packet_count = 0;
        while(!feof(fp)) {
            // Parse the per packet header
            char per_packet_header[16];
            fread(per_packet_header, 16, 1, fp);
            // Get the packet length
            uint32_t packet_length, untrunc_packet_length;
            memcpy(&packet_length, per_packet_header + 8, 4);
            // Get the un-truncated packet length
            memcpy(&untrunc_packet_length, per_packet_header + 12, 4);

            if (packet_length != untrunc_packet_length) {
               printf("Packet length and untruncated length do not match.\n"); 
            }

            // Parse the packet data aka our frame
            // This is part of the Link Layer Protocol
            char frame[packet_length];
            fread(frame, packet_length, 1, fp);

            if (sizeof(per_packet_header) > 0 && sizeof(frame) > 0) {
                packet_count++;
            }

            printf("\tFrame %d:\n", packet_count);
            printf("\t\tLength:              %u\n", packet_length);
            printf("\t\tUntruncated length:  %u\n\n", untrunc_packet_length);

            // Using the ethernet frame we need to:
            // 1. Determine the version of the wrapped IP Datagram (IPv6 or IPv4).
            // 2. Verify that all the IP Datagrams have the same format.
            // 3. Print the source and destination MAC Addresses.
            printf("\tLink Layer (Ethernet):\n");
            uint64_t mac_dest, mac_src;
            uint16_t ethertype;
            memcpy(&mac_dest, frame, 6);
            memcpy(&mac_src, frame + 6, 6);
            memcpy(&ethertype, frame + 12, 2);

            printf("\t\tMac destination:     %lx\n", __builtin_bswap64(mac_dest) >> 16);
            printf("\t\tMac source:          %lx\n", __builtin_bswap64(mac_src) >> 16);
            printf("\t\tEthertype:           %s\n\n", (ethertype == 8) ? "IPv4" : "IPv6");

            // Parse the Datagram aka IP header
            // This is part of the Network Layer Protocol
            // This layer always starts at byte 15 _I think_
            printf("\tNetwork Layer (IP):\n");
            uint32_t src_ip, dest_ip;
            uint16_t datagram_length, be_datagram_length;
            uint8_t ip_header_byte;
            memcpy(&ip_header_byte, frame + 14, 1);
            memcpy(&datagram_length, frame + 16, 2);
            be_datagram_length = __builtin_bswap16(datagram_length);
            memcpy(&src_ip, frame + 26, 4);
            memcpy(&dest_ip, frame + 30, 4);

            unsigned mask = (1 << 4) - 1;
            uint8_t internet_header_length = ((ip_header_byte & mask) & 0x0f) * 4;

            // char datagram[be_datagram_length];
            // fread(datagram, be_datagram_length, 1, fp);


            printf("\t\tTotal length:        %u\n", be_datagram_length);
            printf("\t\tHeader length:       %u\n", internet_header_length);
            printf("\t\tPayload length:      %u\n", be_datagram_length - internet_header_length);
            printf("\t\tSource IP:           %u\n", __builtin_bswap32(src_ip));
            printf("\t\tDestination IP:      %u\n", __builtin_bswap32(dest_ip));


            // Parse the TCP Headers
            printf("\t\t----------------------------\n");
        }

        printf("Total packet count: %d\n", packet_count);
    }

    fclose(fp);
    return 0;
}
