package com.mf;

public class Example {
  public static void main(String[] args) throws InterruptedException {
    Thread th = new Thread() {
      public void run() {
        final Reader r = new Reader();
        
        r.addListener(new Listener() {
          private volatile boolean enabled = true;
          
          @Override
          public void onResult(String result) {
            disable();
            System.out.println("ON RESULT: " + result);
            enable();
          }
          
          @Override
          public synchronized boolean isEnabled() {
            return enabled;
          }
          
          private synchronized void enable() {
            enabled = true;
          }
          
          private synchronized void disable() {
            enabled = false;
          }
        });   
      }
    };
    
    th.start();
    th.join();
  }
}