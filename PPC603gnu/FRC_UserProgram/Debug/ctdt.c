/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */


void _GLOBAL__I__ZN21AnesthesiologistDriveC2EP33AnesthesiologistOperatorInterface();

void _GLOBAL__I__ZN24AnesthesiologistLauncherC2EP27AnesthesiologistManipulator();

void _GLOBAL__I__ZN27AnesthesiologistManipulatorC2Ev();

void _GLOBAL__I__ZN33AnesthesiologistOperatorInterfaceC2Ev();

void _GLOBAL__I_step();

extern void (*_ctors[])();
void (*_ctors[])() =
    {
    _GLOBAL__I__ZN21AnesthesiologistDriveC2EP33AnesthesiologistOperatorInterface,
    _GLOBAL__I__ZN24AnesthesiologistLauncherC2EP27AnesthesiologistManipulator,
    _GLOBAL__I__ZN27AnesthesiologistManipulatorC2Ev,
    _GLOBAL__I__ZN33AnesthesiologistOperatorInterfaceC2Ev,
    _GLOBAL__I_step,
    0
    };

void _GLOBAL__D__ZN21AnesthesiologistDriveC2EP33AnesthesiologistOperatorInterface();

void _GLOBAL__D__ZN24AnesthesiologistLauncherC2EP27AnesthesiologistManipulator();

void _GLOBAL__D__ZN27AnesthesiologistManipulatorC2Ev();

void _GLOBAL__D__ZN33AnesthesiologistOperatorInterfaceC2Ev();

void _GLOBAL__D_step();

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    _GLOBAL__D__ZN21AnesthesiologistDriveC2EP33AnesthesiologistOperatorInterface,
    _GLOBAL__D__ZN24AnesthesiologistLauncherC2EP27AnesthesiologistManipulator,
    _GLOBAL__D__ZN27AnesthesiologistManipulatorC2Ev,
    _GLOBAL__D__ZN33AnesthesiologistOperatorInterfaceC2Ev,
    _GLOBAL__D_step,
    0
    };
