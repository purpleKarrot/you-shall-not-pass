<script setup>
defineProps({
  from: { type: String, required: true },
  to: { type: String, required: true },
  at: { type: Number, required: true },
  color: { type: String, default: '#fecaca' },
})
</script>

<template>
  <span class="morph-phrase">
    <!-- Reserves the position without determining the marker width -->
    <span class="morph-size" aria-hidden="true">
      {{ from }}
    </span>

    <span
      v-click.hide="[at, 999]"
      class="morph-word"
      :style="{ '--marker-color': color }"
    >
      {{ from }}
    </span>

    <span
      v-click="[at, 999]"
      class="morph-word"
      :style="{ '--marker-color': color }"
    >
      {{ to }}
    </span>
  </span>
</template>

<style scoped>
.morph-phrase {
  position: relative;
  display: inline-block;
  vertical-align: baseline;
}

.morph-size {
  visibility: hidden;
  white-space: nowrap;
}

.morph-word {
  position: absolute;
  left: 0;
  top: 0;
  white-space: nowrap;
  z-index: 0;
}

.morph-word::before {
  content: '';
  position: absolute;
  z-index: -1;

  left: -0.04em;
  right: -0.04em;
  top: 0.25em;
  bottom: 0.02em;

  background: var(--marker-color);
  opacity: 0.7;

  clip-path: polygon(
    0% 18%, 8% 10%, 18% 14%, 30% 8%, 43% 13%,
    56% 7%, 69% 12%, 82% 8%, 100% 11%,
    98% 82%, 90% 88%, 78% 84%, 66% 91%,
    53% 86%, 40% 92%, 27% 87%, 15% 91%,
    6% 85%, 1% 89%
  );

  transform: rotate(-0.5deg);
}
</style>
