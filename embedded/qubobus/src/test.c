/*
 * Simple diagnostic program that prints out the lengths of various Qubobus messages.
 */

#include "../include/qubobus.h"

#if QUBOBUS_PROTOCOL_VERSION != 1
#error Update me with new message defs!
#endif

#include <stdio.h>

int message(const char *name, uint16_t type, size_t size);
int data(const char *name, uint16_t type, size_t size);
int error(const char *name, uint16_t type, size_t size);

#define EMPTY 0
int main() { 
    int success = 1;
    /* Tests for protocol-wide messages */
    success &= message(
            "Announce Message", 
            MT_ANNOUNCE, 
            EMPTY);
    success &= message(
            "Protocol Message", 
            MT_PROTOCOL, 
            sizeof(struct Protocol_Info));
    success &= message(
            "Keepalive Message", 
            MT_KEEPALIVE, 
            EMPTY);
    success &= error(
            "Protocol Mismatch Error", 
            E_ID_PROTOCOL, 
            EMPTY);
    success &= error(
            "Checksum Mismatch Error", 
            E_ID_CHECKSUM, 
            EMPTY);
    success &= error(
            "Connection Timeout Error", 
            E_ID_TIMEOUT, 
            EMPTY);

    /* Tests involving the embedded subsystem */
    success &= data(
            "Embedded Status Request", 
            D_ID_EMBEDDED_STATUS_REQUEST, 
            EMPTY);
    success &= data(
            "Embedded Status", 
            D_ID_EMBEDDED_STATUS, 
            sizeof(struct Embedded_Status));
    success &= error(
            "Embedded Overload", 
            E_ID_EMBEDDED_OVERLOAD, 
            EMPTY);
    success &= error(
            "Embedded Memory", 
            E_ID_EMBEDDED_MEMORY, 
            EMPTY);
    success &= error(
            "Embedded Page Fault", 
            E_ID_EMBEDDED_PAGE_FAULT, 
            EMPTY);
    success &= error(
            "Embedded Assert", 
            E_ID_EMBEDDED_ASSERT, 
            EMPTY);

    /* Tests for messages involving the safety subsystem */
    success &= data(
            "Safety Status Request", 
            D_ID_SAFETY_STATUS_REQUEST, 
            EMPTY);
    success &= data(
            "Safety Status", 
            D_ID_SAFETY_STATUS, 
            sizeof(struct Safety_Status));
    success &= data(
            "Safety Set Safe", 
            D_ID_SAFETY_SET_SAFE, 
            EMPTY);
    success &= data(
            "Safety Set Unsafe", 
            D_ID_SAFETY_SET_UNSAFE, 
            EMPTY);

    /* Tests for messages involving the battery subsystem */
    success &= data(
            "Battery Status Request", 
            D_ID_BATTERY_STATUS_REQUEST, 
            sizeof(struct Battery_Status_Request));
    success &= data(
            "Battery Status", 
            D_ID_BATTERY_STATUS, 
            sizeof(struct Battery_Status));
    success &= data(
            "Battery Config", 
            D_ID_BATTERY_CONFIG, 
            sizeof(struct Battery_Config));
    success &= data(
            "Battery Shutdown", 
            D_ID_BATTERY_SHUTDOWN, 
            sizeof(struct Battery_Shutdown));
    success &= error(
            "Battery Unreachable", 
            E_ID_BATTERY_UNREACHABLE, 
            EMPTY);
    success &= error(
            "Battery Disconnect", 
            E_ID_BATTERY_DISCONNECT, 
            EMPTY);
    success &= error(
            "Battery Environment", 
            E_ID_BATTERY_ENVIRONMENT, 
            EMPTY);

    /* Tests involving the power subsystem */
    success &= data(
            "Power Status Request", 
            D_ID_POWER_STATUS_REQUEST, 
            EMPTY);
    success &= data(
            "Power Status", 
            D_ID_POWER_STATUS, 
            sizeof(struct Power_Status));
    success &= data(
            "Power Config", 
            D_ID_POWER_CONFIG, 
            sizeof(struct Power_Config));
    success &= data(
            "Power Enable", 
            D_ID_POWER_ENABLE, 
            sizeof(struct Power_Enable));
    success &= data(
            "Power Disable", 
            D_ID_POWER_DISABLE, 
            sizeof(struct Power_Disable));
    success &= error(
            "Power Unreachable", 
            E_ID_POWER_UNREACHABLE, 
            EMPTY);
    success &= error(
            "Power Overvolt", 
            E_ID_POWER_OVERVOLT, 
            EMPTY);
    success &= error(
            "Power Undervolt", 
            E_ID_POWER_UNDERVOLT, 
            EMPTY);
    success &= error(
            "Power Overcurrent", 
            E_ID_POWER_OVERCURRENT, 
            EMPTY);

    /* Tests involving the thruster subsystem */
    success &= data(
            "Thruster Set", 
            D_ID_THRUSTER_SET, 
            sizeof(struct Thruster_Set));
    success &= data(
            "Thruster Current Request", 
            D_ID_THRUSTER_CURRENT_REQUEST, 
            sizeof(struct Thruster_Current_Request));
    success &= data(
            "Thruster Current", 
            D_ID_THRUSTER_CURRENT, 
            sizeof(struct Thruster_Current));
    success &= data(
            "Thruster Config", 
            D_ID_THRUSTER_CONFIG, 
            sizeof(struct Thruster_Config));
    success &= error(
            "Thruster Unreachable", 
            E_ID_THRUSTER_UNREACHABLE, 
            EMPTY);
    success &= error(
            "Thruster Overcurrent", 
            E_ID_THRUSTER_OVERCURRENT, 
            EMPTY);
    success &= error(
            "Thruster Watchdog", 
            E_ID_THRUSTER_WATCHDOG, 
            EMPTY);

    /* Tests involving the pneumatics subsystem */
    success &= data(
            "Pneumatics Set", 
            D_ID_PNEUMATICS_SET, 
            sizeof(struct Pneumatics_Set));
    success &= error(
            "Pneumatics Unreachable", 
            E_ID_PNEUMATICS_UNREACHABLE, 
            EMPTY);

    /* Tests involving the depth sensor subsystem */
    success &= data(
            "Depth Request", 
            D_ID_DEPTH_STATUS_REQUEST, 
            EMPTY);
    success &= data(
            "Depth Measurement", 
            D_ID_DEPTH_STATUS, 
            sizeof(struct Depth_Status));
    success &= data(
            "Depth Config", 
            D_ID_DEPTH_CONFIG, 
            sizeof(struct Depth_Config));
    success &= error(
            "Depth Unreachable", 
            E_ID_DEPTH_UNREACHABLE, 
            EMPTY);
    success &= error(
            "Depth Warning", 
            E_ID_DEPTH_WARNING, 
            EMPTY);


    if (success) {
        printf("No unrecoverable errors found!\n");
    }
    return !success;
}

/* Function indicating the definition of a message. */
int message(const char *name, uint16_t type, size_t size) {
    size += sizeof(struct Message_Header);
    size += sizeof(struct Message_Footer);
    printf("%s: %d\n",name, size);
    if (size%4) {
        printf("WARNING: not 4-byte aligned!\n");
    }
    return 1;
}

/* Function indicating the declaration of a single data message type. */
int data(const char *name, uint16_t type, size_t size) {
    /* Table of data types that may be defined. */
    static int types[QUBOBUS_DATA_TYPES] = {0};

    /* If the type indicated is garbage, error out and dont keep checking the type. */
    if (type >= QUBOBUS_DATA_TYPES) {
        printf("ERROR: IMPROPER DATA TYPE ID!\n");
        return 0;
    } 
    /* If there was a type definition collision, error out. */
    if (types[type]) {
        printf("ERROR: DATA TYPE ID REUSED!\n");
        return 0;
    }
    types[type] = 1;

    /* Defer to the main message definition checker for printing. */
    return message(name, MT_DATA, size + sizeof(struct Data_Header));
}

/* Function indicating the declaration of a single error message type. */
int error(const char *name, uint16_t type, size_t size) {
    /* Table of error types that may be defined. */
    static int types[QUBOBUS_ERROR_TYPES] = {0};

    /* If the type indicated is garbage, error out and dont keep checking the type. */
    if (type >= QUBOBUS_ERROR_TYPES) {
        printf("ERROR: IMPROPER ERROR TYPE ID!\n");
        return 0;
    } 
    /* If there was a type definition collision, error out. */
    if (types[type]) {
        printf("ERROR: ERROR TYPE ID REUSED!\n");
        return 0;
    }
    types[type] = 1;

    /* Defer to the main message definition checker for printing. */
    return message(name, MT_ERROR, size + sizeof(struct Error_Header));
}

