from filecmp import cmp


NUM_TESTS = 9

TOLERANCE = 1


def compare(input_path, output_path):
    if not cmp(input_path, output_path):
        with open(input_path) as input_file, open(output_path) as output_file:
            input_file.readline()
            input_file.readline()
            input_file.readline()

            output_file.readline()
            output_file.readline()
            output_file.readline()

            for input_line, output_line in zip(input_file, output_file):
                if abs(int(output_line) - int(input_line)) > TOLERANCE:
                    print('NÃO PASSOU EM TESTE: {} diferente de {}'.format(input_path, output_path))
                    return 0

    return 1


def main():
    num_passed = 0

    for t in range(1, NUM_TESTS + 1):
        num_passed += compare('integration_inputs/{}.pgm'.format(t), 'integration_outputs/{}.pgm'.format(t))
        num_passed += compare('integration_golds/{}-lp.pgm'.format(t), 'integration_outputs/{}-lp.pgm'.format(t))
        num_passed += compare('integration_golds/{}-hp.pgm'.format(t), 'integration_outputs/{}-hp.pgm'.format(t))

    print('passou em {} de {} testes'.format(num_passed, 3 * NUM_TESTS))


if __name__ == '__main__':
    main()
