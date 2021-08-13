/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testmidi;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Optional;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sound.midi.InvalidMidiDataException;
import javax.sound.midi.MidiDevice;
import javax.sound.midi.MidiSystem;
import static javax.sound.midi.MidiSystem.getMidiDevice;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Receiver;
import javax.sound.midi.ShortMessage;
import static javax.sound.midi.ShortMessage.NOTE_ON;
import javax.sound.midi.Synthesizer;

/**
 *
 * @author billaud
 */
public class TestMidi {

    public static Optional<Synthesizer> openSynthesizer() {
        MidiDevice.Info[] infos = MidiSystem.getMidiDeviceInfo();
        for (MidiDevice.Info info : infos) {
            try {
                Synthesizer synth = (Synthesizer) MidiSystem.getMidiDevice(info);
                if (synth != null) {
                    synth.open();
                    return Optional.of(synth);
                }
            } catch (MidiUnavailableException ex) {
            }
        }
        return Optional.empty();
    }

    public static void main(String[] args)  {
        openSynthesizer().ifPresent(TestMidi::playOnSynth);
    }

    private static void playOnSynth(Synthesizer synth)   {
        System.out.println("Playing");
                
                
        try {
            Receiver receiver = synth.getReceiver();
            ShortMessage msg = new ShortMessage(NOTE_ON, 1, 60, 93);
            receiver.send(msg, -1);
        } catch (MidiUnavailableException ex) {
            Logger.getLogger(TestMidi.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidMidiDataException ex) {
            Logger.getLogger(TestMidi.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        System.out.println("Done");
    }
    }
