// FUN_1029ee90
// Purpose:
//   Classifies a packet / message opcode and returns a normalized type code.
//   Acts as a wrapper around switchD_1029eeac with additional validation.
//
// Called from:
//   1029e8f8
//   1029e9b6
//   1029ea33
//   1029ecb5
//
// Returns:
//   >= 0  : valid mapped opcode
//   -1    : invalid / unsupported opcode
//   3     : special control opcode (0x1C7)

int __stdcall FUN_1029ee90(unsigned int opcode)
{
    int result;

    // Fast-path special opcode
    if (opcode == 0x1C7)
    {
        return 3;
    }

    // Dispatch via jump-table switch
    result = switchD_1029eeac(opcode);

    // Normalize invalid cases
    if (result == -1)
    {
        return -1;
    }

    return result;
}
