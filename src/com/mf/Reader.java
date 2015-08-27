package com.mf;

import java.util.ArrayList;
import java.util.List;

public class Reader {
  private List<Listener> listeners = new ArrayList<Listener>();
  
  static {
    System.loadLibrary("evdev");
  }
  
  private native void init(String devName);
  
  public Reader() {
    this("/dev/input/event19");
  }
  
  public Reader(final String evdevDevice) {
    new Thread() {
      @Override
      public void run() {
        this.setName("READER THREAD");
        
        init(evdevDevice);
      }
    }.start();
  }
  
  private synchronized void callback(String result) {
    for (Listener l : listeners) {
      if (l.isEnabled())
        l.onResult(result);
    }
  }
  
  public void addListener(Listener l) {
    listeners.add(l);
  }
  
  public void removeListener(Listener l) {
    listeners.remove(l);
  }
}