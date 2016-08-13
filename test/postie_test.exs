defmodule PostieTest do
  use ExUnit.Case, async: false

  describe "normalization" do
    test "can expand an address" do

      addresses = Postie.expand_address("Quatre-vingt-douze Ave des Champs-Élysées")
      assert is_list(addresses)
      assert Enum.any?(addresses, &(&1 == "92 avenue des champs-elysees")) == true

    end

    test "handles various formats" do

      sample_data = [
        {"One-hundred twenty E 96th St", "120 east 96th street"},
        {"C/ Ocho, P.I. 4", "calle ocho poligono industrial 4"},
        {"V XX Settembre, 20", "via 20 settembre 20"},
        {"Quatre vingt douze R. de l'Église", "92 rue de l'eglise"},
        {"ул Каретный Ряд, д 4, строение 7", "улица каретныи ряд дом 4 строение 7"},
        {"ул Каретный Ряд, д 4, строение 7", "ulitsa karetnyy ryad dom 4 stroyeniye 7"},
        {"Marktstrasse 14", "markt strasse 14"}
      ]

      for {input, expected_output} <- sample_data do
        output = Postie.expand_address(input)
        assert is_list(output)
        assert Enum.any?(output, &(&1 == expected_output)) == true
      end

    end
  end

  describe "parsing" do
    test "can parse an address" do

      example_addresses = [
        {
          "The Book Club 100-106 Leonard St Shoreditch London EC2A 4RH, United Kingdom",
          [:house, :house_number, :road, :suburb, :city, :postcode, :country]
        },
        {
          "781 Franklin Ave Crown Heights Brooklyn 11216 USA",
          [:house_number, :road, :suburb, :state_district, :postcode, :country]
        }
      ]

      for {input_address, expected_dataset} <- example_addresses do
        address = Postie.parse_address(input_address)
        assert address |> Enum.map(fn({key, _value}) -> key end) == expected_dataset
        assert address |> Enum.each(fn({_key, value}) ->
          assert is_binary(value)
        end)
      end

    end
  end

end
