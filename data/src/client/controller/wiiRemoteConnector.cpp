#ifdef _ENABLE_WII
WiiRemoteConnector::WiiRemoteConnector()
{
}

WiiRemote *WiiRemoteConnector::connect(const char *id)
{
    wiimote_t wiimote = WIIMOTE_INIT;
    if (wiimote_connect(&wiimote, id) < 0)
    {
        return NULL;
    }
    wiimote.led.one = 1;
    return new WiiRemote(wiimote);
}
#endif